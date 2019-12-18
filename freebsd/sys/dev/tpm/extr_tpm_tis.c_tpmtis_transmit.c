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
struct tpm_sc {size_t pending_data_length; int /*<<< orphan*/  dev; int /*<<< orphan*/ * buf; void* intr_type; int /*<<< orphan*/  mem_res; int /*<<< orphan*/  dev_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_BARRIER_WRITE ; 
 int EIO ; 
 int RD4 (struct tpm_sc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 size_t TPM_BUFSIZE ; 
 size_t TPM_HEADER_SIZE ; 
 void* TPM_INT_STS_DATA_AVAIL ; 
 void* TPM_INT_STS_VALID ; 
 int /*<<< orphan*/  TPM_STS ; 
 int /*<<< orphan*/  TPM_STS_CMD_START ; 
 int TPM_STS_DATA_AVAIL ; 
 int TPM_STS_DATA_EXPECTED ; 
 int TPM_STS_VALID ; 
 int TPM_TIMEOUT_C ; 
 int /*<<< orphan*/  WR4 (struct tpm_sc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* be32toh (int) ; 
 int /*<<< orphan*/  bus_barrier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int tpm20_get_timeout (int) ; 
 int /*<<< orphan*/  tpm_wait_for_u32 (struct tpm_sc*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  tpmtis_go_ready (struct tpm_sc*) ; 
 int /*<<< orphan*/  tpmtis_read_bytes (struct tpm_sc*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpmtis_relinquish_locality (struct tpm_sc*) ; 
 int /*<<< orphan*/  tpmtis_request_locality (struct tpm_sc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpmtis_write_bytes (struct tpm_sc*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
tpmtis_transmit(struct tpm_sc *sc, size_t length)
{
	size_t bytes_available;
	uint32_t mask, curr_cmd;
	int timeout;

	sx_assert(&sc->dev_lock, SA_XLOCKED);

	if (!tpmtis_request_locality(sc, 0)) {
		device_printf(sc->dev,
		    "Failed to obtain locality\n");
		return (EIO);
	}
	if (!tpmtis_go_ready(sc)) {
		device_printf(sc->dev,
		    "Failed to switch to ready state\n");
		return (EIO);
	}
	if (!tpmtis_write_bytes(sc, length, sc->buf)) {
		device_printf(sc->dev,
		    "Failed to write cmd to device\n");
		return (EIO);
	}

	mask = TPM_STS_VALID;
	sc->intr_type = TPM_INT_STS_VALID;
	if (!tpm_wait_for_u32(sc, TPM_STS, mask, mask, TPM_TIMEOUT_C)) {
		device_printf(sc->dev,
		    "Timeout while waiting for valid bit\n");
		return (EIO);
	}
	if (RD4(sc, TPM_STS) & TPM_STS_DATA_EXPECTED) {
		device_printf(sc->dev,
		    "Device expects more data even though we already"
		    " sent everything we had\n");
		return (EIO);
	}

	/*
	 * Calculate timeout for current command.
	 * Command code is passed in bytes 6-10.
	 */
	curr_cmd = be32toh(*(uint32_t *) (&sc->buf[6]));
	timeout = tpm20_get_timeout(curr_cmd);

	WR4(sc, TPM_STS, TPM_STS_CMD_START);
	bus_barrier(sc->mem_res, TPM_STS, 4, BUS_SPACE_BARRIER_WRITE);

	mask = TPM_STS_DATA_AVAIL | TPM_STS_VALID;
	sc->intr_type = TPM_INT_STS_DATA_AVAIL;
	if (!tpm_wait_for_u32(sc, TPM_STS, mask, mask, timeout)) {
		device_printf(sc->dev,
		    "Timeout while waiting for device to process cmd\n");
		/*
		 * Switching to ready state also cancels processing
		 * current command
		 */
		if (!tpmtis_go_ready(sc))
			return (EIO);

		/*
		 * After canceling a command we should get a response,
		 * check if there is one.
		 */
		sc->intr_type = TPM_INT_STS_DATA_AVAIL;
		if (!tpm_wait_for_u32(sc, TPM_STS, mask, mask, TPM_TIMEOUT_C))
			return (EIO);
	}
	/* Read response header. Length is passed in bytes 2 - 6. */
	if(!tpmtis_read_bytes(sc, TPM_HEADER_SIZE, sc->buf)) {
		device_printf(sc->dev,
		    "Failed to read response header\n");
		return (EIO);
	}
	bytes_available = be32toh(*(uint32_t *) (&sc->buf[2]));

	if (bytes_available > TPM_BUFSIZE || bytes_available < TPM_HEADER_SIZE) {
		device_printf(sc->dev,
		    "Incorrect response size: %zu\n",
		    bytes_available);
		return (EIO);
	}
	if(!tpmtis_read_bytes(sc, bytes_available - TPM_HEADER_SIZE,
	    &sc->buf[TPM_HEADER_SIZE])) {
		device_printf(sc->dev,
		    "Failed to read response\n");
		return (EIO);
	}
	tpmtis_relinquish_locality(sc);
	sc->pending_data_length = bytes_available;

	return (0);
}