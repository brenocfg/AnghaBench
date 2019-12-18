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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct bxe_softc {int dummy; } ;
typedef  scalar_t__ elink_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,int) ; 
 scalar_t__ ELINK_STATUS_ERROR ; 
 scalar_t__ ELINK_STATUS_OK ; 
 scalar_t__ ELINK_STATUS_TIMEOUT ; 
 int MCPR_IMC_COMMAND_ENABLE ; 
 int MCPR_IMC_COMMAND_IMC_STATUS_BITSHIFT ; 
 int MCPR_IMC_COMMAND_OPERATION_BITSHIFT ; 
 int MCPR_IMC_COMMAND_READ_OP ; 
 int MCPR_IMC_COMMAND_TRANSFER_ADDRESS_BITSHIFT ; 
 int MCPR_IMC_COMMAND_WRITE_OP ; 
 scalar_t__ MCP_REG_MCPR_IMC_COMMAND ; 
 scalar_t__ MCP_REG_MCPR_IMC_DATAREG0 ; 
 scalar_t__ MCP_REG_MCPR_IMC_SLAVE_CONTROL ; 
 int REG_RD (struct bxe_softc*,scalar_t__) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int) ; 

__attribute__((used)) static elink_status_t elink_bsc_read(struct bxe_softc *sc,
			  uint8_t sl_devid,
			  uint16_t sl_addr,
			  uint8_t lc_addr,
			  uint8_t xfer_cnt,
			  uint32_t *data_array)
{
	uint32_t val, i;
	elink_status_t rc = ELINK_STATUS_OK;

	if (xfer_cnt > 16) {
		ELINK_DEBUG_P1(sc, "invalid xfer_cnt %d. Max is 16 bytes\n",
					xfer_cnt);
		return ELINK_STATUS_ERROR;
	}

	xfer_cnt = 16 - lc_addr;

	/* Enable the engine */
	val = REG_RD(sc, MCP_REG_MCPR_IMC_COMMAND);
	val |= MCPR_IMC_COMMAND_ENABLE;
	REG_WR(sc, MCP_REG_MCPR_IMC_COMMAND, val);

	/* Program slave device ID */
	val = (sl_devid << 16) | sl_addr;
	REG_WR(sc, MCP_REG_MCPR_IMC_SLAVE_CONTROL, val);

	/* Start xfer with 0 byte to update the address pointer ???*/
	val = (MCPR_IMC_COMMAND_ENABLE) |
	      (MCPR_IMC_COMMAND_WRITE_OP <<
		MCPR_IMC_COMMAND_OPERATION_BITSHIFT) |
		(lc_addr << MCPR_IMC_COMMAND_TRANSFER_ADDRESS_BITSHIFT) | (0);
	REG_WR(sc, MCP_REG_MCPR_IMC_COMMAND, val);

	/* Poll for completion */
	i = 0;
	val = REG_RD(sc, MCP_REG_MCPR_IMC_COMMAND);
	while (((val >> MCPR_IMC_COMMAND_IMC_STATUS_BITSHIFT) & 0x3) != 1) {
		DELAY(10);
		val = REG_RD(sc, MCP_REG_MCPR_IMC_COMMAND);
		if (i++ > 1000) {
			ELINK_DEBUG_P1(sc, "wr 0 byte timed out after %d try\n",
								i);
			rc = ELINK_STATUS_TIMEOUT;
			break;
		}
	}
	if (rc == ELINK_STATUS_TIMEOUT)
		return rc;

	/* Start xfer with read op */
	val = (MCPR_IMC_COMMAND_ENABLE) |
		(MCPR_IMC_COMMAND_READ_OP <<
		MCPR_IMC_COMMAND_OPERATION_BITSHIFT) |
		(lc_addr << MCPR_IMC_COMMAND_TRANSFER_ADDRESS_BITSHIFT) |
		  (xfer_cnt);
	REG_WR(sc, MCP_REG_MCPR_IMC_COMMAND, val);

	/* Poll for completion */
	i = 0;
	val = REG_RD(sc, MCP_REG_MCPR_IMC_COMMAND);
	while (((val >> MCPR_IMC_COMMAND_IMC_STATUS_BITSHIFT) & 0x3) != 1) {
		DELAY(10);
		val = REG_RD(sc, MCP_REG_MCPR_IMC_COMMAND);
		if (i++ > 1000) {
			ELINK_DEBUG_P1(sc, "rd op timed out after %d try\n", i);
			rc = ELINK_STATUS_TIMEOUT;
			break;
		}
	}
	if (rc == ELINK_STATUS_TIMEOUT)
		return rc;

	for (i = (lc_addr >> 2); i < 4; i++) {
		data_array[i] = REG_RD(sc, (MCP_REG_MCPR_IMC_DATAREG0 + i*4));
#ifdef __BIG_ENDIAN
		data_array[i] = ((data_array[i] & 0x000000ff) << 24) |
				((data_array[i] & 0x0000ff00) << 8) |
				((data_array[i] & 0x00ff0000) >> 8) |
				((data_array[i] & 0xff000000) >> 24);
#endif
	}
	return rc;
}