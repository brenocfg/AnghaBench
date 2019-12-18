#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int16_t ;
struct TYPE_6__ {scalar_t__ vtb_type; int vtb_size; int vtb_tail; } ;
typedef  TYPE_1__ sc_vtb_t ;

/* Variables and functions */
 scalar_t__ VTB_FRAMEBUFFER ; 
 scalar_t__ VTB_RINGBUFFER ; 
 int /*<<< orphan*/  bcopy (void*,void*,int) ; 
 int /*<<< orphan*/  bcopy_fromio (scalar_t__,scalar_t__,int) ; 
 int imin (int,int) ; 
 scalar_t__ sc_vtb_pointer (TYPE_1__*,int) ; 
 int vtb_wrap (TYPE_1__*,int,int) ; 

void
sc_vtb_append(sc_vtb_t *vtb1, int from, sc_vtb_t *vtb2, int count)
{
	int len;

	if (vtb2->vtb_type != VTB_RINGBUFFER)
		return;

	while (count > 0) {
		len = imin(count, vtb2->vtb_size - vtb2->vtb_tail);
#ifndef __sparc64__
		if (vtb1->vtb_type == VTB_FRAMEBUFFER)
			bcopy_fromio(sc_vtb_pointer(vtb1, from),
				     sc_vtb_pointer(vtb2, vtb2->vtb_tail),
				     len*sizeof(u_int16_t));
		else
#endif
			bcopy((void *)sc_vtb_pointer(vtb1, from),
			      (void *)sc_vtb_pointer(vtb2, vtb2->vtb_tail),
			      len*sizeof(u_int16_t));
		from += len;
		count -= len;
		vtb2->vtb_tail = vtb_wrap(vtb2, vtb2->vtb_tail, len);
	}
}