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
struct via_info {int dummy; } ;
struct via_chinfo {scalar_t__ rbase; } ;

/* Variables and functions */
 int SGD_CONTROL_STOP ; 
 int SGD_STATUS_EOL ; 
 int SGD_STATUS_FLAG ; 
 scalar_t__ VIA_RP_CONTROL ; 
 scalar_t__ VIA_RP_STATUS ; 
 int /*<<< orphan*/  via_wr (struct via_info*,scalar_t__,int,int) ; 

__attribute__((used)) static void
via8233chan_reset(struct via_info *via, struct via_chinfo *ch)
{
	via_wr(via, ch->rbase + VIA_RP_CONTROL, SGD_CONTROL_STOP, 1);
	via_wr(via, ch->rbase + VIA_RP_CONTROL, 0x00, 1);
	via_wr(via, ch->rbase + VIA_RP_STATUS,
	    SGD_STATUS_EOL | SGD_STATUS_FLAG, 1);
}