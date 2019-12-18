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
struct vio_driver_state {int dr_state; } ;

/* Variables and functions */
 int VIO_DR_STATE_RXREG ; 
 int VIO_DR_STATE_RXREQ ; 
 int VIO_DR_STATE_TXREG ; 
 int VIO_DR_STATE_TXREQ ; 

__attribute__((used)) static int all_drings_registered(struct vio_driver_state *vio)
{
	int need_rx, need_tx;

	need_rx = (vio->dr_state & VIO_DR_STATE_RXREQ);
	need_tx = (vio->dr_state & VIO_DR_STATE_TXREQ);

	if (need_rx &&
	    !(vio->dr_state & VIO_DR_STATE_RXREG))
		return 0;

	if (need_tx &&
	    !(vio->dr_state & VIO_DR_STATE_TXREG))
		return 0;

	return 1;
}