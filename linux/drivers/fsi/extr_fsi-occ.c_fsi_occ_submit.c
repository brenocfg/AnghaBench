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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct occ_response {scalar_t__ seq_no; struct occ_response* data; int /*<<< orphan*/  return_status; int /*<<< orphan*/  data_length; } ;
struct occ {int /*<<< orphan*/  occ_lock; int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENODEV ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  OCC_CMD_IN_PRG_WAIT_MS ; 
 int /*<<< orphan*/  OCC_RESP_CMD_IN_PRG ; 
 int /*<<< orphan*/  OCC_SRAM_CMD_ADDR ; 
 scalar_t__ OCC_SRAM_RSP_ADDR ; 
 int /*<<< orphan*/  OCC_TIMEOUT_MS ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,size_t,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 struct occ* dev_get_drvdata (struct device*) ; 
 int get_unaligned_be16 (int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int occ_getsram (struct occ*,scalar_t__,struct occ_response*,int) ; 
 int occ_putsram (struct occ*,int /*<<< orphan*/ ,void const*,size_t) ; 
 int occ_trigger_attn (struct occ*) ; 
 int occ_verify_checksum (struct occ_response*,int) ; 
 int /*<<< orphan*/  schedule_timeout (unsigned long const) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

int fsi_occ_submit(struct device *dev, const void *request, size_t req_len,
		   void *response, size_t *resp_len)
{
	const unsigned long timeout = msecs_to_jiffies(OCC_TIMEOUT_MS);
	const unsigned long wait_time =
		msecs_to_jiffies(OCC_CMD_IN_PRG_WAIT_MS);
	struct occ *occ = dev_get_drvdata(dev);
	struct occ_response *resp = response;
	u8 seq_no;
	u16 resp_data_length;
	unsigned long start;
	int rc;

	if (!occ)
		return -ENODEV;

	if (*resp_len < 7) {
		dev_dbg(dev, "Bad resplen %zd\n", *resp_len);
		return -EINVAL;
	}

	mutex_lock(&occ->occ_lock);

	/* Extract the seq_no from the command (first byte) */
	seq_no = *(const u8 *)request;
	rc = occ_putsram(occ, OCC_SRAM_CMD_ADDR, request, req_len);
	if (rc)
		goto done;

	rc = occ_trigger_attn(occ);
	if (rc)
		goto done;

	/* Read occ response header */
	start = jiffies;
	do {
		rc = occ_getsram(occ, OCC_SRAM_RSP_ADDR, resp, 8);
		if (rc)
			goto done;

		if (resp->return_status == OCC_RESP_CMD_IN_PRG ||
		    resp->seq_no != seq_no) {
			rc = -ETIMEDOUT;

			if (time_after(jiffies, start + timeout)) {
				dev_err(occ->dev, "resp timeout status=%02x "
					"resp seq_no=%d our seq_no=%d\n",
					resp->return_status, resp->seq_no,
					seq_no);
				goto done;
			}

			set_current_state(TASK_UNINTERRUPTIBLE);
			schedule_timeout(wait_time);
		}
	} while (rc);

	/* Extract size of response data */
	resp_data_length = get_unaligned_be16(&resp->data_length);

	/* Message size is data length + 5 bytes header + 2 bytes checksum */
	if ((resp_data_length + 7) > *resp_len) {
		rc = -EMSGSIZE;
		goto done;
	}

	dev_dbg(dev, "resp_status=%02x resp_data_len=%d\n",
		resp->return_status, resp_data_length);

	/* Grab the rest */
	if (resp_data_length > 1) {
		/* already got 3 bytes resp, also need 2 bytes checksum */
		rc = occ_getsram(occ, OCC_SRAM_RSP_ADDR + 8,
				 &resp->data[3], resp_data_length - 1);
		if (rc)
			goto done;
	}

	*resp_len = resp_data_length + 7;
	rc = occ_verify_checksum(resp, resp_data_length);

 done:
	mutex_unlock(&occ->occ_lock);

	return rc;
}