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
typedef  void* vm_offset_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct TYPE_4__ {int vtb_type; int vtb_cols; int vtb_rows; int vtb_size; scalar_t__ vtb_buffer; scalar_t__ vtb_flags; scalar_t__ vtb_tail; } ;
typedef  TYPE_1__ sc_vtb_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ VTB_ALLOCED ; 
#define  VTB_FRAMEBUFFER 130 
#define  VTB_MEMORY 129 
#define  VTB_RINGBUFFER 128 
 scalar_t__ VTB_VALID ; 
 int /*<<< orphan*/  bzero (void*,int) ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sc_vtb_pointer (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
sc_vtb_init(sc_vtb_t *vtb, int type, int cols, int rows, void *buf, int wait)
{
	vtb->vtb_flags = 0;
	vtb->vtb_type = type;
	vtb->vtb_cols = cols;
	vtb->vtb_rows = rows;
	vtb->vtb_size = cols*rows;
	vtb->vtb_buffer = 0;
	vtb->vtb_tail = 0;

	switch (type) {
	case VTB_MEMORY:
	case VTB_RINGBUFFER:
		if ((buf == NULL) && (cols*rows != 0)) {
			vtb->vtb_buffer =
				(vm_offset_t)malloc(cols*rows*sizeof(u_int16_t),
						    M_DEVBUF, 
						    (wait) ? M_WAITOK : M_NOWAIT);
			if (vtb->vtb_buffer != 0) {
				bzero((void *)sc_vtb_pointer(vtb, 0),
				      cols*rows*sizeof(u_int16_t));
				vtb->vtb_flags |= VTB_ALLOCED;
			}
		} else {
			vtb->vtb_buffer = (vm_offset_t)buf;
		}
		vtb->vtb_flags |= VTB_VALID;
		break;
#ifndef __sparc64__
	case VTB_FRAMEBUFFER:
		vtb->vtb_buffer = (vm_offset_t)buf;
		vtb->vtb_flags |= VTB_VALID;
		break;
#endif
	default:
		break;
	}
}