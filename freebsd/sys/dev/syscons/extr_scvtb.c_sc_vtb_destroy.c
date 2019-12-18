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
struct TYPE_3__ {int vtb_type; int vtb_flags; scalar_t__ vtb_buffer; scalar_t__ vtb_tail; scalar_t__ vtb_size; scalar_t__ vtb_rows; scalar_t__ vtb_cols; } ;
typedef  TYPE_1__ sc_vtb_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int VTB_ALLOCED ; 
 int VTB_INVALID ; 
#define  VTB_MEMORY 129 
#define  VTB_RINGBUFFER 128 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 

void
sc_vtb_destroy(sc_vtb_t *vtb)
{
	vm_offset_t p;

	vtb->vtb_cols = 0;
	vtb->vtb_rows = 0;
	vtb->vtb_size = 0;
	vtb->vtb_tail = 0;

	p = vtb->vtb_buffer;
	vtb->vtb_buffer = 0;
	switch (vtb->vtb_type) {
	case VTB_MEMORY:
	case VTB_RINGBUFFER:
		if ((vtb->vtb_flags & VTB_ALLOCED) && (p != 0))
			free((void *)p, M_DEVBUF);
		break;
	default:
		break;
	}
	vtb->vtb_flags = 0;
	vtb->vtb_type = VTB_INVALID;
}