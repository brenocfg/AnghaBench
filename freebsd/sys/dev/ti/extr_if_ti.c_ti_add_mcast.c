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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int u_int ;
struct ti_softc {int ti_hwrev; int /*<<< orphan*/  ti_dev; } ;
struct ti_cmd_desc {int dummy; } ;
struct sockaddr_dl {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct ti_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ LLADDR (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  TI_CMD_ADD_MCAST_ADDR ; 
 int /*<<< orphan*/  TI_CMD_EXT_ADD_MCAST ; 
 int /*<<< orphan*/  TI_DO_CMD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_DO_CMD_EXT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TI_GCR_MAR0 ; 
 int /*<<< orphan*/  TI_GCR_MAR1 ; 
#define  TI_HWREV_TIGON 129 
#define  TI_HWREV_TIGON_II 128 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
ti_add_mcast(void *arg, struct sockaddr_dl *sdl, u_int count)
{
	struct ti_softc *sc = arg;
	struct ti_cmd_desc cmd;
	uint16_t *m;
	uint32_t ext[2] = {0, 0};

	m = (uint16_t *)LLADDR(sdl);

	switch (sc->ti_hwrev) {
	case TI_HWREV_TIGON:
		CSR_WRITE_4(sc, TI_GCR_MAR0, htons(m[0]));
		CSR_WRITE_4(sc, TI_GCR_MAR1, (htons(m[1]) << 16) | htons(m[2]));
		TI_DO_CMD(TI_CMD_ADD_MCAST_ADDR, 0, 0);
		break;
	case TI_HWREV_TIGON_II:
		ext[0] = htons(m[0]);
		ext[1] = (htons(m[1]) << 16) | htons(m[2]);
		TI_DO_CMD_EXT(TI_CMD_EXT_ADD_MCAST, 0, 0, (caddr_t)&ext, 2);
		break;
	default:
		device_printf(sc->ti_dev, "unknown hwrev\n");
		return (0);
	}
	return (1);
}