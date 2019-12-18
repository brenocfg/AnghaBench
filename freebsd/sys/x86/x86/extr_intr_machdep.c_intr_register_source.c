#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct intsrc {scalar_t__ is_handlers; int /*<<< orphan*/  is_event; TYPE_1__* is_pic; } ;
typedef  int /*<<< orphan*/  mask_fn ;
struct TYPE_2__ {int (* pic_vector ) (struct intsrc*) ;scalar_t__ pic_eoi_source; scalar_t__ pic_enable_source; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct intsrc** interrupt_sources ; 
 int /*<<< orphan*/  intr_assign_cpu ; 
 int /*<<< orphan*/  intr_disable_src ; 
 int intr_event_create (int /*<<< orphan*/ *,struct intsrc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  intr_event_destroy (int /*<<< orphan*/ ) ; 
 int intr_pic_registered (TYPE_1__*) ; 
 int /*<<< orphan*/  intrcnt_register (struct intsrc*) ; 
 int /*<<< orphan*/  intrsrc_lock ; 
 int num_io_irqs ; 
 int stub1 (struct intsrc*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
intr_register_source(struct intsrc *isrc)
{
	int error, vector;

	KASSERT(intr_pic_registered(isrc->is_pic), ("unregistered PIC"));
	vector = isrc->is_pic->pic_vector(isrc);
	KASSERT(vector < num_io_irqs, ("IRQ %d too large (%u irqs)", vector,
	    num_io_irqs));
	if (interrupt_sources[vector] != NULL)
		return (EEXIST);
	error = intr_event_create(&isrc->is_event, isrc, 0, vector,
	    intr_disable_src, (mask_fn)isrc->is_pic->pic_enable_source,
	    (mask_fn)isrc->is_pic->pic_eoi_source, intr_assign_cpu, "irq%d:",
	    vector);
	if (error)
		return (error);
	sx_xlock(&intrsrc_lock);
	if (interrupt_sources[vector] != NULL) {
		sx_xunlock(&intrsrc_lock);
		intr_event_destroy(isrc->is_event);
		return (EEXIST);
	}
	intrcnt_register(isrc);
	interrupt_sources[vector] = isrc;
	isrc->is_handlers = 0;
	sx_xunlock(&intrsrc_lock);
	return (0);
}