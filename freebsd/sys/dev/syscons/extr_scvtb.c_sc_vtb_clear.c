#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ vtb_type; int /*<<< orphan*/  vtb_size; } ;
typedef  TYPE_1__ sc_vtb_t ;

/* Variables and functions */
 scalar_t__ VTB_FRAMEBUFFER ; 
 int /*<<< orphan*/  fillw (int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fillw_io (int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ sc_vtb_pointer (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
sc_vtb_clear(sc_vtb_t *vtb, int c, int attr)
{
#ifndef __sparc64__
	if (vtb->vtb_type == VTB_FRAMEBUFFER)
		fillw_io(attr | c, sc_vtb_pointer(vtb, 0), vtb->vtb_size);
	else
#endif
		fillw(attr | c, (void *)sc_vtb_pointer(vtb, 0), vtb->vtb_size);
}