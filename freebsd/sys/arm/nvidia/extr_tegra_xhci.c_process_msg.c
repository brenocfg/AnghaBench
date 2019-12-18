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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct tegra_xhci_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  clk_xusb_ss; int /*<<< orphan*/  clk_xusb_falcon_src; } ;

/* Variables and functions */
 int MBOX_CMD_ACK ; 
#define  MBOX_CMD_AIRPLANE_MODE_DISABLED 144 
#define  MBOX_CMD_AIRPLANE_MODE_ENABLED 143 
#define  MBOX_CMD_DBC_WAKE_STACK 142 
#define  MBOX_CMD_DEC_FALC_CLOCK 141 
#define  MBOX_CMD_DEC_SSPI_CLOCK 140 
#define  MBOX_CMD_DISABLE_SS_LFPS_DETECTION 139 
#define  MBOX_CMD_ENABLE_SS_LFPS_DETECTION 138 
#define  MBOX_CMD_HSIC_PRETEND_CONNECT 137 
#define  MBOX_CMD_INC_FALC_CLOCK 136 
#define  MBOX_CMD_INC_SSPI_CLOCK 135 
 int MBOX_CMD_NAK ; 
#define  MBOX_CMD_RESET_SSPI 134 
#define  MBOX_CMD_SAVE_DFE_CTLE_CTX 133 
#define  MBOX_CMD_SET_BW 132 
#define  MBOX_CMD_SET_SS_PWR_GATING 131 
#define  MBOX_CMD_SET_SS_PWR_UNGATING 130 
#define  MBOX_CMD_START_HSIC_IDLE 129 
#define  MBOX_CMD_STOP_HSIC_IDLE 128 
 int clk_get_freq (int /*<<< orphan*/ ,int*) ; 
 int clk_set_freq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
process_msg(struct tegra_xhci_softc *sc, uint32_t req_cmd, uint32_t req_data,
    uint32_t *resp_cmd, uint32_t *resp_data)
{
	uint64_t freq;
	int rv;

	/* In most cases, data are echoed back. */
	*resp_data = req_data;
	switch (req_cmd) {
	case MBOX_CMD_INC_FALC_CLOCK:
	case MBOX_CMD_DEC_FALC_CLOCK:
		rv = clk_set_freq(sc->clk_xusb_falcon_src, req_data * 1000ULL,
		    0);
		if (rv == 0) {
			rv = clk_get_freq(sc->clk_xusb_falcon_src, &freq);
			*resp_data = (uint32_t)(freq / 1000);
		}
		*resp_cmd = rv == 0 ? MBOX_CMD_ACK: MBOX_CMD_NAK;
		break;

	case MBOX_CMD_INC_SSPI_CLOCK:
	case MBOX_CMD_DEC_SSPI_CLOCK:
		rv = clk_set_freq(sc->clk_xusb_ss, req_data * 1000ULL,
		    0);
		if (rv == 0) {
			rv = clk_get_freq(sc->clk_xusb_ss, &freq);
			*resp_data = (uint32_t)(freq / 1000);
		}
		*resp_cmd = rv == 0 ? MBOX_CMD_ACK: MBOX_CMD_NAK;
		break;

	case MBOX_CMD_SET_BW:
		/* No respense is expected. */
		*resp_cmd = 0;
		break;

	case MBOX_CMD_SET_SS_PWR_GATING:
	case MBOX_CMD_SET_SS_PWR_UNGATING:
		*resp_cmd = MBOX_CMD_NAK;
		break;

	case MBOX_CMD_SAVE_DFE_CTLE_CTX:
		/* Not implemented yet. */
		*resp_cmd = MBOX_CMD_ACK;
		break;


	case MBOX_CMD_START_HSIC_IDLE:
	case MBOX_CMD_STOP_HSIC_IDLE:
		/* Not implemented yet. */
		*resp_cmd = MBOX_CMD_NAK;
		break;

	case MBOX_CMD_DISABLE_SS_LFPS_DETECTION:
	case MBOX_CMD_ENABLE_SS_LFPS_DETECTION:
		/* Not implemented yet. */
		*resp_cmd = MBOX_CMD_NAK;
		break;

	case MBOX_CMD_AIRPLANE_MODE_ENABLED:
	case MBOX_CMD_AIRPLANE_MODE_DISABLED:
	case MBOX_CMD_DBC_WAKE_STACK:
	case MBOX_CMD_HSIC_PRETEND_CONNECT:
	case MBOX_CMD_RESET_SSPI:
		device_printf(sc->dev,
		    "Received unused/unexpected command: %u\n", req_cmd);
		*resp_cmd = 0;
		break;

	default:
		device_printf(sc->dev,
		    "Received unknown command: %u\n", req_cmd);
	}
}