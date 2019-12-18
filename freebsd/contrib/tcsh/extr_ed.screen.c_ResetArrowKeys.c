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
struct TYPE_3__ {int /*<<< orphan*/  cmd; } ;
struct TYPE_4__ {void* type; TYPE_1__ fun; } ;

/* Variables and functions */
 size_t A_K_DN ; 
 size_t A_K_EN ; 
 size_t A_K_HO ; 
 size_t A_K_LT ; 
 size_t A_K_RT ; 
 size_t A_K_UP ; 
 int /*<<< orphan*/  F_CHARBACK ; 
 int /*<<< orphan*/  F_CHARFWD ; 
 int /*<<< orphan*/  F_DOWN_HIST ; 
 int /*<<< orphan*/  F_TOBEG ; 
 int /*<<< orphan*/  F_TOEND ; 
 int /*<<< orphan*/  F_UP_HIST ; 
 void* XK_CMD ; 
 TYPE_2__* arrow ; 

void
ResetArrowKeys(void)
{
    arrow[A_K_DN].fun.cmd = F_DOWN_HIST;
    arrow[A_K_DN].type    = XK_CMD;

    arrow[A_K_UP].fun.cmd = F_UP_HIST;
    arrow[A_K_UP].type    = XK_CMD;

    arrow[A_K_LT].fun.cmd = F_CHARBACK;
    arrow[A_K_LT].type    = XK_CMD;

    arrow[A_K_RT].fun.cmd = F_CHARFWD;
    arrow[A_K_RT].type    = XK_CMD;

    arrow[A_K_HO].fun.cmd = F_TOBEG;
    arrow[A_K_HO].type    = XK_CMD;

    arrow[A_K_EN].fun.cmd = F_TOEND;
    arrow[A_K_EN].type    = XK_CMD;
}