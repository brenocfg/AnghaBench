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
struct intsrc {scalar_t__ is_handlers; TYPE_1__* is_pic; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pic_disable_intr ) (struct intsrc*) ;int /*<<< orphan*/  (* pic_disable_source ) (struct intsrc*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PIC_NO_EOI ; 
 int intr_event_remove_handler (void*) ; 
 struct intsrc* intr_handler_source (void*) ; 
 int /*<<< orphan*/  intrcnt_updatename (struct intsrc*) ; 
 int /*<<< orphan*/  intrsrc_lock ; 
 int /*<<< orphan*/  stub1 (struct intsrc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct intsrc*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
intr_remove_handler(void *cookie)
{
	struct intsrc *isrc;
	int error;

	isrc = intr_handler_source(cookie);
	error = intr_event_remove_handler(cookie);
	if (error == 0) {
		sx_xlock(&intrsrc_lock);
		isrc->is_handlers--;
		if (isrc->is_handlers == 0) {
			isrc->is_pic->pic_disable_source(isrc, PIC_NO_EOI);
			isrc->is_pic->pic_disable_intr(isrc);
		}
		intrcnt_updatename(isrc);
		sx_xunlock(&intrsrc_lock);
	}
	return (error);
}