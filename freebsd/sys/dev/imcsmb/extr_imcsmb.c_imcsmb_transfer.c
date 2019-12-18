#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int u_char ;
struct imcsmb_softc {TYPE_1__* regs; int /*<<< orphan*/  imcsmb_pci; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  smb_cntl; int /*<<< orphan*/  smb_stat; int /*<<< orphan*/  smb_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int IMCSMB_CMD_TRIGGER_BIT ; 
 int IMCSMB_CMD_WORD_ACCESS ; 
 int IMCSMB_CMD_WRITE_BIT ; 
 int IMCSMB_CNTL_CLK_OVERRIDE ; 
 int IMCSMB_CNTL_DTI_MASK ; 
 int IMCSMB_CNTL_POLL_EN ; 
 int IMCSMB_CNTL_WRITE_DISABLE_BIT ; 
 int IMCSMB_STATUS_BUSY_BIT ; 
 int IMCSMB_STATUS_BUS_ERROR_BIT ; 
 int IMCSMB_STATUS_READ_DATA_VALID ; 
 int IMCSMB_STATUS_WRITE_DATA_DONE ; 
 int SMB_ENOACK ; 
 int SMB_ENOERR ; 
 int SMB_ETIMEOUT ; 
 struct imcsmb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int htobe16 (int) ; 
 int hz ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
imcsmb_transfer(device_t dev, u_char slave, char cmd, void *data, int word_op,
    int write_op)
{
	struct imcsmb_softc *sc;
	int i;
	int rc;
	uint32_t cmd_val;
	uint32_t cntl_val;
	uint32_t orig_cntl_val;
	uint32_t stat_val;
	uint16_t *word;
	uint16_t lword;
	uint8_t *byte;
	uint8_t lbyte;

	sc = device_get_softc(dev);
	byte = data;
	word = data;
	lbyte = *byte;
	lword = *word;

	/* We modify the value of the control register; save the original, so
	 * we can restore it later
	 */
	orig_cntl_val = pci_read_config(sc->imcsmb_pci,
	    sc->regs->smb_cntl, 4);
	cntl_val = orig_cntl_val;

	/*
	 * Set up the SMBCNTL register
	 */

	/* [31:28] Clear the existing value of the DTI bits, then set them to
	 * the four high bits of the slave address.
	 */
	cntl_val &= ~IMCSMB_CNTL_DTI_MASK;
	cntl_val |= ((uint32_t) slave & 0xf0) << 24;

	/* [27:27] Set the CLK_OVERRIDE bit, to enable normal operation */
	cntl_val |= IMCSMB_CNTL_CLK_OVERRIDE;

	/* [26:26] Clear the WRITE_DISABLE bit; the datasheet says this isn't
	 * necessary, but empirically, it is.
	 */
	cntl_val &= ~IMCSMB_CNTL_WRITE_DISABLE_BIT;

	/* [9:9] Clear the POLL_EN bit, to stop the hardware TSOD polling. */
	cntl_val &= ~IMCSMB_CNTL_POLL_EN;

	/*
	 * Set up the SMBCMD register
	 */

	/* [31:31] Set the TRIGGER bit; when this gets written, the controller
	 * will issue the command.
	 */
	cmd_val = IMCSMB_CMD_TRIGGER_BIT;

	/* [29:29] For word operations, set the WORD_ACCESS bit. */
	if (word_op) {
		cmd_val |= IMCSMB_CMD_WORD_ACCESS;
	}

	/* [27:27] For write operations, set the WRITE bit. */
	if (write_op) {
		cmd_val |= IMCSMB_CMD_WRITE_BIT;
	}

	/* [26:24] The three non-DTI, non-R/W bits of the slave address. */
	cmd_val |= (uint32_t) ((slave & 0xe) << 23);

	/* [23:16] The command (offset in the case of an EEPROM, or register in
	 * the case of TSOD or NVDIMM controller).
	 */
	cmd_val |= (uint32_t) ((uint8_t) cmd << 16);

	/* [15:0] The data to be written for a write operation. */
	if (write_op) {
		if (word_op) {
			/* The datasheet says the controller uses different
			 * endianness for word operations on I2C vs SMBus!
			 *      I2C: [15:8] = MSB; [7:0] = LSB
			 *      SMB: [15:8] = LSB; [7:0] = MSB
			 * As a practical matter, this controller is very
			 * specifically for use with DIMMs, the SPD (and
			 * NVDIMM controllers) are only accessed as bytes,
			 * the temperature sensor is only accessed as words, and
			 * the temperature sensors are I2C. Thus, byte-swap the
			 * word.
			 */
			lword = htobe16(lword);
		} else {
			/* For byte operations, the data goes in the LSB, and
			 * the MSB is a don't care.
			 */
			lword = (uint16_t) (lbyte & 0xff);
		}
		cmd_val |= lword;
	}

	/* Write the updated value to the control register first, to disable
	 * the hardware TSOD polling.
	 */
	pci_write_config(sc->imcsmb_pci, sc->regs->smb_cntl, cntl_val, 4);

	/* Poll on the BUSY bit in the status register until clear, or timeout.
	 * We just cleared the auto-poll bit, so we need to make sure the device
	 * is idle before issuing a command. We can safely timeout after 35 ms,
	 * as this is the maximum time the SMBus spec allows for a transaction.
	 */
	for (i = 4; i != 0; i--) {
		stat_val = pci_read_config(sc->imcsmb_pci, sc->regs->smb_stat,
		    4);
		if ((stat_val & IMCSMB_STATUS_BUSY_BIT) == 0) {
			break;
		}
		pause("imcsmb", 10 * hz / 1000);
	}

	if (i == 0) {
		device_printf(sc->dev,
		    "transfer: timeout waiting for device to settle\n");
	}

	/* Now that polling has stopped, we can write the command register. This
	 * starts the SMBus command.
	 */
	pci_write_config(sc->imcsmb_pci, sc->regs->smb_cmd, cmd_val, 4);

	/* Wait for WRITE_DATA_DONE/READ_DATA_VALID to be set, or timeout and
	 * fail. We wait up to 35ms.
	 */
	for (i = 35000; i != 0; i -= 10)
	{
		DELAY(10);
		stat_val = pci_read_config(sc->imcsmb_pci, sc->regs->smb_stat,
		    4);
		/* For a write, the bits holding the data contain the data being
		 * written. You'd think that would cause the READ_DATA_VALID bit
		 * to be cleared, because the data bits no longer contain valid
		 * data from the most recent read operation. While that would be
		 * logical, that's not the case here: READ_DATA_VALID is only
		 * cleared when starting a read operation, and WRITE_DATA_DONE
		 * is only cleared when starting a write operation.
		 */
		if (write_op) {
			if ((stat_val & IMCSMB_STATUS_WRITE_DATA_DONE) != 0) {
				break;
			}
		} else {
			if ((stat_val & IMCSMB_STATUS_READ_DATA_VALID) != 0) {
				break;
			}
		}
	}
	if (i == 0) {
		rc = SMB_ETIMEOUT;
		device_printf(dev, "transfer timeout\n");
		goto out;
	}

	/* It is generally the case that this bit indicates non-ACK, but it
	 * could also indicate other bus errors. There's no way to tell the
	 * difference.
	 */
	if ((stat_val & IMCSMB_STATUS_BUS_ERROR_BIT) != 0) {
		/* While it is not documented, empirically, SPD page-change
		 * commands (writes with DTI = 0x60) always complete with the
		 * error bit set. So, ignore it in those cases.
		 */
		if ((slave & 0xf0) != 0x60) {
			rc = SMB_ENOACK;
			goto out;
		}
	}

	/* For a read operation, copy the data out */
	if (write_op == 0) {
		if (word_op) {
			/* The data is returned in bits [15:0]; as discussed
			 * above, byte-swap.
			 */
			lword = (uint16_t) (stat_val & 0xffff);
			lword = htobe16(lword);
			*word = lword;
		} else {
			/* The data is returned in bits [7:0] */
			lbyte = (uint8_t) (stat_val & 0xff);
			*byte = lbyte;
		}
	}

	/* A lack of an error is, de facto, success. */
	rc = SMB_ENOERR;

out:
	/* Restore the original value of the control register. */
	pci_write_config(sc->imcsmb_pci, sc->regs->smb_cntl, orig_cntl_val, 4);
	return (rc);
}