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
typedef  int uint32_t ;
struct tpmcrb_sc {size_t cmd_buf_size; scalar_t__ rsp_off; int /*<<< orphan*/  cmd_off; } ;
struct tpm_sc {int pending_data_length; int /*<<< orphan*/ * buf; int /*<<< orphan*/  mem_res; int /*<<< orphan*/  dev; int /*<<< orphan*/  dev_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_BARRIER_WRITE ; 
 int E2BIG ; 
 int EIO ; 
 int /*<<< orphan*/  OR4 (struct tpm_sc*,int /*<<< orphan*/ ,int) ; 
 int RD4 (struct tpm_sc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int TPM_BUFSIZE ; 
 int /*<<< orphan*/  TPM_CRB_CTRL_CANCEL ; 
 int /*<<< orphan*/  TPM_CRB_CTRL_CANCEL_CMD ; 
 int /*<<< orphan*/  TPM_CRB_CTRL_REQ ; 
 int TPM_CRB_CTRL_REQ_GO_IDLE ; 
 int TPM_CRB_CTRL_REQ_GO_READY ; 
 int /*<<< orphan*/  TPM_CRB_CTRL_START ; 
 int TPM_CRB_CTRL_START_CMD ; 
 int /*<<< orphan*/  TPM_CRB_CTRL_STS ; 
 int TPM_CRB_CTRL_STS_ERR_BIT ; 
 int TPM_CRB_CTRL_STS_IDLE_BIT ; 
 int TPM_HEADER_SIZE ; 
 int TPM_TIMEOUT_C ; 
 int /*<<< orphan*/  WR4 (struct tpm_sc*,int /*<<< orphan*/ ,int) ; 
 int be32toh (int) ; 
 int /*<<< orphan*/  bus_barrier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_read_region_stream_1 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bus_write_region_stream_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int tpm20_get_timeout (int) ; 
 int /*<<< orphan*/  tpm_wait_for_u32 (struct tpm_sc*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  tpmcrb_cancel_cmd (struct tpm_sc*) ; 
 int /*<<< orphan*/  tpmcrb_relinquish_locality (struct tpm_sc*) ; 
 int /*<<< orphan*/  tpmcrb_request_locality (struct tpm_sc*,int /*<<< orphan*/ ) ; 

int
tpmcrb_transmit(struct tpm_sc *sc, size_t length)
{
	struct tpmcrb_sc *crb_sc;
	uint32_t mask, curr_cmd;
	int timeout, bytes_available;

	crb_sc = (struct tpmcrb_sc *)sc;

	sx_assert(&sc->dev_lock, SA_XLOCKED);

	if (length > crb_sc->cmd_buf_size) {
		device_printf(sc->dev,
		    "Requested transfer is bigger than buffer size\n");
		return (E2BIG);
	}

	if (RD4(sc, TPM_CRB_CTRL_STS) & TPM_CRB_CTRL_STS_ERR_BIT) {
		device_printf(sc->dev,
		    "Device has Error bit set\n");
		return (EIO);
	}
	if (!tpmcrb_request_locality(sc, 0)) {
		device_printf(sc->dev,
		    "Failed to obtain locality\n");
		return (EIO);
	}
	/* Clear cancellation bit */
	WR4(sc, TPM_CRB_CTRL_CANCEL, !TPM_CRB_CTRL_CANCEL_CMD);

	/* Switch device to idle state if necessary */
	if (!(RD4(sc, TPM_CRB_CTRL_STS) & TPM_CRB_CTRL_STS_IDLE_BIT)) {
		OR4(sc, TPM_CRB_CTRL_REQ, TPM_CRB_CTRL_REQ_GO_IDLE);

		mask = TPM_CRB_CTRL_STS_IDLE_BIT;
		if (!tpm_wait_for_u32(sc, TPM_CRB_CTRL_STS,
			    mask, mask, TPM_TIMEOUT_C)) {
			device_printf(sc->dev,
			    "Failed to transition to idle state\n");
			return (EIO);
		}
	}
	/* Switch to ready state */
	OR4(sc, TPM_CRB_CTRL_REQ, TPM_CRB_CTRL_REQ_GO_READY);

	mask = TPM_CRB_CTRL_REQ_GO_READY;
	if (!tpm_wait_for_u32(sc, TPM_CRB_CTRL_STS,
		    mask, !mask, TPM_TIMEOUT_C)) {
		device_printf(sc->dev,
		    "Failed to transition to ready state\n");
		return (EIO);
	}

	/*
	 * Calculate timeout for current command.
	 * Command code is passed in bytes 6-10.
	 */
	curr_cmd = be32toh(*(uint32_t *) (&sc->buf[6]));
	timeout = tpm20_get_timeout(curr_cmd);

	/* Send command and tell device to process it. */
	bus_write_region_stream_1(sc->mem_res, crb_sc->cmd_off,
	    sc->buf, length);
	bus_barrier(sc->mem_res, crb_sc->cmd_off,
	    length, BUS_SPACE_BARRIER_WRITE);

	WR4(sc, TPM_CRB_CTRL_START, TPM_CRB_CTRL_START_CMD);
	bus_barrier(sc->mem_res, TPM_CRB_CTRL_START,
	    4, BUS_SPACE_BARRIER_WRITE);

	mask = ~0;
	if (!tpm_wait_for_u32(sc, TPM_CRB_CTRL_START, mask, ~mask, timeout)) {
		device_printf(sc->dev,
		    "Timeout while waiting for device to process cmd\n");
		if (!tpmcrb_cancel_cmd(sc))
			return (EIO);
	}

	/* Read response header. Length is passed in bytes 2 - 6. */
	bus_read_region_stream_1(sc->mem_res, crb_sc->rsp_off,
	    sc->buf, TPM_HEADER_SIZE);
	bytes_available = be32toh(*(uint32_t *) (&sc->buf[2]));

	if (bytes_available > TPM_BUFSIZE || bytes_available < TPM_HEADER_SIZE) {
		device_printf(sc->dev,
		    "Incorrect response size: %d\n",
		    bytes_available);
		return (EIO);
	}

	bus_read_region_stream_1(sc->mem_res, crb_sc->rsp_off + TPM_HEADER_SIZE,
	      &sc->buf[TPM_HEADER_SIZE], bytes_available - TPM_HEADER_SIZE);

	OR4(sc, TPM_CRB_CTRL_REQ, TPM_CRB_CTRL_REQ_GO_IDLE);

	tpmcrb_relinquish_locality(sc);
	sc->pending_data_length = bytes_available;

	return (0);
}