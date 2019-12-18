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
struct brcmf_sdio_dev {int state; int /*<<< orphan*/  bus_if; } ;
typedef  enum brcmf_sdiod_state { ____Placeholder_brcmf_sdiod_state } brcmf_sdiod_state ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_BUS_DOWN ; 
 int /*<<< orphan*/  BRCMF_BUS_UP ; 
#define  BRCMF_SDIOD_DATA 129 
#define  BRCMF_SDIOD_DOWN 128 
 int BRCMF_SDIOD_NOMEDIUM ; 
 int /*<<< orphan*/  brcmf_bus_change_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void brcmf_sdiod_change_state(struct brcmf_sdio_dev *sdiodev,
			      enum brcmf_sdiod_state state)
{
	if (sdiodev->state == BRCMF_SDIOD_NOMEDIUM ||
	    state == sdiodev->state)
		return;

	//brcmf_dbg(TRACE, "%d -> %d\n", sdiodev->state, state);
	switch (sdiodev->state) {
	case BRCMF_SDIOD_DATA:
		/* any other state means bus interface is down */
		brcmf_bus_change_state(sdiodev->bus_if, BRCMF_BUS_DOWN);
		break;
	case BRCMF_SDIOD_DOWN:
		/* transition from DOWN to DATA means bus interface is up */
		if (state == BRCMF_SDIOD_DATA)
			brcmf_bus_change_state(sdiodev->bus_if, BRCMF_BUS_UP);
		break;
	default:
		break;
	}
	sdiodev->state = state;
}