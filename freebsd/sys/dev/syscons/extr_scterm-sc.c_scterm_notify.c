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
typedef  int /*<<< orphan*/  scr_stat ;

/* Variables and functions */
#define  SC_TE_NOTIFY_VTSWITCH_IN 129 
#define  SC_TE_NOTIFY_VTSWITCH_OUT 128 

__attribute__((used)) static void
scterm_notify(scr_stat *scp, int event)
{
	switch (event) {
	case SC_TE_NOTIFY_VTSWITCH_IN:
		break;
	case SC_TE_NOTIFY_VTSWITCH_OUT:
		break;
	}
}