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
struct TYPE_3__ {int status; } ;
typedef  TYPE_1__ scr_stat ;

/* Variables and functions */
 int MOUSE_CUTTING ; 
 int MOUSE_VISIBLE ; 

__attribute__((used)) static void
mouse_cut_end(scr_stat *scp) 
{
    if (scp->status & MOUSE_VISIBLE)
	scp->status &= ~MOUSE_CUTTING;
}