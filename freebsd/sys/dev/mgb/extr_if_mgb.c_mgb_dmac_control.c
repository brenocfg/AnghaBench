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
struct mgb_softc {int dummy; } ;
typedef  enum mgb_dmac_cmd { ____Placeholder_mgb_dmac_cmd } mgb_dmac_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_REG (struct mgb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  DMAC_RESET 130 
#define  DMAC_START 129 
#define  DMAC_STOP 128 
 int /*<<< orphan*/  MGB_DMAC_CMD ; 
 int /*<<< orphan*/  MGB_DMAC_CMD_RESET (int,int) ; 
 int /*<<< orphan*/  MGB_DMAC_CMD_START (int,int) ; 
 int /*<<< orphan*/  MGB_DMAC_CMD_STOP (int,int) ; 
 int mgb_wait_for_bits (struct mgb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mgb_dmac_control(struct mgb_softc *sc, int start, int channel,
    enum mgb_dmac_cmd cmd)
{
	int error = 0;

	switch (cmd) {
	case DMAC_RESET:
		CSR_WRITE_REG(sc, MGB_DMAC_CMD,
		    MGB_DMAC_CMD_RESET(start, channel));
		error = mgb_wait_for_bits(sc, MGB_DMAC_CMD, 0,
		    MGB_DMAC_CMD_RESET(start, channel));
		break;

	case DMAC_START:
		/*
		 * NOTE: this simplifies the logic, since it will never
		 * try to start in STOP_PENDING, but it also increases work.
		 */
		error = mgb_dmac_control(sc, start, channel, DMAC_STOP);
		if (error != 0)
			return error;
		CSR_WRITE_REG(sc, MGB_DMAC_CMD,
		    MGB_DMAC_CMD_START(start, channel));
		break;

	case DMAC_STOP:
		CSR_WRITE_REG(sc, MGB_DMAC_CMD,
		    MGB_DMAC_CMD_STOP(start, channel));
		error = mgb_wait_for_bits(sc, MGB_DMAC_CMD,
		    MGB_DMAC_CMD_STOP(start, channel),
		    MGB_DMAC_CMD_START(start, channel));
		break;
	}
	return error;
}