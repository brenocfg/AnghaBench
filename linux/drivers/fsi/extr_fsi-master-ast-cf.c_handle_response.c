#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u8 ;
struct fsi_msg {int dummy; } ;
struct fsi_master_acf {scalar_t__ trace_enabled; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int /*<<< orphan*/  FSI_CRC_ERR_RETRIES ; 
 int /*<<< orphan*/  FSI_MASTER_DPOLL_CLOCKS ; 
 int /*<<< orphan*/  FSI_MASTER_EPOLL_CLOCKS ; 
 int /*<<< orphan*/  FSI_MASTER_MAX_BUSY ; 
#define  FSI_RESP_ACK 131 
#define  FSI_RESP_BUSY 130 
#define  FSI_RESP_ERRA 129 
#define  FSI_RESP_ERRC 128 
 int /*<<< orphan*/  build_dpoll_command (struct fsi_msg*,int) ; 
 int /*<<< orphan*/  build_epoll_command (struct fsi_msg*,int) ; 
 int clock_zeros (struct fsi_master_acf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dump_ucode_trace (struct fsi_master_acf*) ; 
 int read_copro_response (struct fsi_master_acf*,int,int /*<<< orphan*/ *,int*) ; 
 int send_request (struct fsi_master_acf*,struct fsi_msg*,int) ; 
 int /*<<< orphan*/  send_term (struct fsi_master_acf*,int) ; 
 int /*<<< orphan*/  trace_fsi_master_acf_crc_rsp_error (struct fsi_master_acf*,int) ; 
 int /*<<< orphan*/  trace_fsi_master_acf_poll_response_busy (struct fsi_master_acf*,int) ; 

__attribute__((used)) static int handle_response(struct fsi_master_acf *master,
			   uint8_t slave, uint8_t size, void *data)
{
	int busy_count = 0, rc;
	int crc_err_retries = 0;
	struct fsi_msg cmd;
	uint32_t response;
	uint8_t tag;
retry:
	rc = read_copro_response(master, size, &response, &tag);

	/* Handle retries on CRC errors */
	if (rc == -EAGAIN) {
		/* Too many retries ? */
		if (crc_err_retries++ > FSI_CRC_ERR_RETRIES) {
			/*
			 * Pass it up as a -EIO otherwise upper level will retry
			 * the whole command which isn't what we want here.
			 */
			rc = -EIO;
			goto bail;
		}
		trace_fsi_master_acf_crc_rsp_error(master, crc_err_retries);
		if (master->trace_enabled)
			dump_ucode_trace(master);
		rc = clock_zeros(master, FSI_MASTER_EPOLL_CLOCKS);
		if (rc) {
			dev_warn(master->dev,
				 "Error %d clocking zeros for E_POLL\n", rc);
			return rc;
		}
		build_epoll_command(&cmd, slave);
		rc = send_request(master, &cmd, size);
		if (rc) {
			dev_warn(master->dev, "Error %d sending E_POLL\n", rc);
			return -EIO;
		}
		goto retry;
	}
	if (rc)
		return rc;

	switch (tag) {
	case FSI_RESP_ACK:
		if (size && data) {
			if (size == 32)
				*(__be32 *)data = cpu_to_be32(response);
			else if (size == 16)
				*(__be16 *)data = cpu_to_be16(response);
			else
				*(u8 *)data = response;
		}
		break;
	case FSI_RESP_BUSY:
		/*
		 * Its necessary to clock slave before issuing
		 * d-poll, not indicated in the hardware protocol
		 * spec. < 20 clocks causes slave to hang, 21 ok.
		 */
		dev_dbg(master->dev, "Busy, retrying...\n");
		if (master->trace_enabled)
			dump_ucode_trace(master);
		rc = clock_zeros(master, FSI_MASTER_DPOLL_CLOCKS);
		if (rc) {
			dev_warn(master->dev,
				 "Error %d clocking zeros for D_POLL\n", rc);
			break;
		}
		if (busy_count++ < FSI_MASTER_MAX_BUSY) {
			build_dpoll_command(&cmd, slave);
			rc = send_request(master, &cmd, size);
			if (rc) {
				dev_warn(master->dev, "Error %d sending D_POLL\n", rc);
				break;
			}
			goto retry;
		}
		dev_dbg(master->dev,
			"ERR slave is stuck in busy state, issuing TERM\n");
		send_term(master, slave);
		rc = -EIO;
		break;

	case FSI_RESP_ERRA:
		dev_dbg(master->dev, "ERRA received\n");
		if (master->trace_enabled)
			dump_ucode_trace(master);
		rc = -EIO;
		break;
	case FSI_RESP_ERRC:
		dev_dbg(master->dev, "ERRC received\n");
		if (master->trace_enabled)
			dump_ucode_trace(master);
		rc = -EAGAIN;
		break;
	}
 bail:
	if (busy_count > 0) {
		trace_fsi_master_acf_poll_response_busy(master, busy_count);
	}

	return rc;
}