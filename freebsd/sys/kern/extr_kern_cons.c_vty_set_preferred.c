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
 unsigned int VTY_SC ; 
 unsigned int VTY_VT ; 
 unsigned int vty_prefer ; 

void
vty_set_preferred(unsigned vty)
{

	vty_prefer = vty;
#if !defined(DEV_SC)
	vty_prefer &= ~VTY_SC;
#endif
#if !defined(DEV_VT)
	vty_prefer &= ~VTY_VT;
#endif
}