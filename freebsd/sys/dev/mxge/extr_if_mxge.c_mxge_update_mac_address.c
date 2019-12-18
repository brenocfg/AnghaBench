#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_6__ {int* mac_addr; } ;
typedef  TYPE_1__ mxge_softc_t ;
struct TYPE_7__ {int data0; int data1; } ;
typedef  TYPE_2__ mxge_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  MXGEFW_SET_MAC_ADDRESS ; 
 int mxge_send_cmd (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int
mxge_update_mac_address(mxge_softc_t *sc)
{
	mxge_cmd_t cmd;
	uint8_t *addr = sc->mac_addr;
	int status;

	
	cmd.data0 = ((addr[0] << 24) | (addr[1] << 16)
		     | (addr[2] << 8) | addr[3]);

	cmd.data1 = ((addr[4] << 8) | (addr[5]));

	status = mxge_send_cmd(sc, MXGEFW_SET_MAC_ADDRESS, &cmd);
	return status;
}