#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ txd_cur; scalar_t__ txd_ack; } ;
typedef  TYPE_1__ ae_softc_t ;

/* Variables and functions */
 unsigned int AE_TXD_BUFSIZE_DEFAULT ; 

__attribute__((used)) static unsigned int
ae_tx_avail_size(ae_softc_t *sc)
{
	unsigned int avail;
	
	if (sc->txd_cur >= sc->txd_ack)
		avail = AE_TXD_BUFSIZE_DEFAULT - (sc->txd_cur - sc->txd_ack);
	else
		avail = sc->txd_ack - sc->txd_cur;

	return (avail);
}