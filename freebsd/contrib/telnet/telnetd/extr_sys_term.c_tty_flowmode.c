#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ t_startc; scalar_t__ t_stopc; } ;
struct TYPE_4__ {int c_iflag; TYPE_1__ tc; } ;

/* Variables and functions */
 int IXON ; 
 TYPE_2__ termbuf ; 

int
tty_flowmode(void)
{
#ifndef USE_TERMIO
	return(((termbuf.tc.t_startc) > 0 && (termbuf.tc.t_stopc) > 0) ? 1 : 0);
#else
	return((termbuf.c_iflag & IXON) ? 1 : 0);
#endif
}