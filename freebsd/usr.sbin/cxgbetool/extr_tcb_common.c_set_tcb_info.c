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
 int /*<<< orphan*/  g_fcb_info ; 
 int /*<<< orphan*/  g_fcb_info4 ; 
 int /*<<< orphan*/  g_fcb_info5 ; 
 int /*<<< orphan*/  g_fcb_info6 ; 
 int /*<<< orphan*/  g_scb_info ; 
 int /*<<< orphan*/  g_scb_info4 ; 
 int /*<<< orphan*/  g_scb_info5 ; 
 int /*<<< orphan*/  g_scb_info6 ; 
 int g_tN ; 
 int /*<<< orphan*/  g_tcb_info ; 
 int /*<<< orphan*/  g_tcb_info4 ; 
 int /*<<< orphan*/  g_tcb_info5 ; 
 int /*<<< orphan*/  g_tcb_info6 ; 
 int /*<<< orphan*/  set_tidtype (unsigned int) ; 

void
set_tcb_info(unsigned int tidtype, unsigned int cardtype)
{
    set_tidtype(tidtype);

    g_tN = cardtype;
    if (4 == g_tN) {
        g_tcb_info = g_tcb_info4;
        g_scb_info = g_scb_info4;
        g_fcb_info = g_fcb_info4;
    }
    else if (5 == g_tN) {
        g_tcb_info = g_tcb_info5;
        g_scb_info = g_scb_info5;
        g_fcb_info = g_fcb_info5;
    }
    else if (6 == g_tN) {
        g_tcb_info = g_tcb_info6;
        g_scb_info = g_scb_info6;
        g_fcb_info = g_fcb_info6;
    }
}