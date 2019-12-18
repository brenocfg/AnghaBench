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
typedef  scalar_t__ vm_offset_t ;
typedef  int u_int16_t ;
struct TYPE_3__ {scalar_t__ vtb_type; } ;
typedef  TYPE_1__ sc_vtb_t ;

/* Variables and functions */
 scalar_t__ VTB_FRAMEBUFFER ; 
 int /*<<< orphan*/  writew (scalar_t__,int) ; 

vm_offset_t
sc_vtb_putchar(sc_vtb_t *vtb, vm_offset_t p, int c, int a)
{
#ifndef __sparc64__
	if (vtb->vtb_type == VTB_FRAMEBUFFER)
		writew(p, a | c);
	else
#endif
		*(u_int16_t *)p = a | c;
	return (p + sizeof(u_int16_t));
}