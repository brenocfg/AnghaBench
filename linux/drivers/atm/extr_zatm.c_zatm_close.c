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
struct atm_vcc {int /*<<< orphan*/  flags; int /*<<< orphan*/ * dev_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_VF_ADDR ; 
 int /*<<< orphan*/  ATM_VF_READY ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  EVENT (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZATM_VCC (struct atm_vcc*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_rx (struct atm_vcc*) ; 
 int /*<<< orphan*/  close_tx (struct atm_vcc*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zatm_close(struct atm_vcc *vcc)
{
        DPRINTK(">zatm_close\n");
        if (!ZATM_VCC(vcc)) return;
	clear_bit(ATM_VF_READY,&vcc->flags);
        close_rx(vcc);
	EVENT("close_tx\n",0,0);
        close_tx(vcc);
        DPRINTK("zatm_close: done waiting\n");
        /* deallocate memory */
        kfree(ZATM_VCC(vcc));
	vcc->dev_data = NULL;
	clear_bit(ATM_VF_ADDR,&vcc->flags);
}