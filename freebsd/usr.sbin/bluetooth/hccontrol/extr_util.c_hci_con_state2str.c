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

/* Variables and functions */
 int SIZE (char const* const*) ; 

char const *
hci_con_state2str(int state)
{
	static char const * const	t[] = {
		/* NG_HCI_CON_CLOSED */           "CLOSED",
		/* NG_HCI_CON_W4_LP_CON_RSP */    "W4_LP_CON_RSP",
		/* NG_HCI_CON_W4_CONN_COMPLETE */ "W4_CONN_COMPLETE",
		/* NG_HCI_CON_OPEN */             "OPEN"
        };

	return (state >= SIZE(t)? "UNKNOWN" : t[state]);
}