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
typedef  size_t u_int ;
struct intsrc {TYPE_1__* is_pic; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pic_reprogram_pin ) (struct intsrc*) ;} ;

/* Variables and functions */
 struct intsrc** interrupt_sources ; 
 int /*<<< orphan*/  intrsrc_lock ; 
 size_t num_io_irqs ; 
 int /*<<< orphan*/  stub1 (struct intsrc*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

void
intr_reprogram(void)
{
	struct intsrc *is;
	u_int v;

	sx_xlock(&intrsrc_lock);
	for (v = 0; v < num_io_irqs; v++) {
		is = interrupt_sources[v];
		if (is == NULL)
			continue;
		if (is->is_pic->pic_reprogram_pin != NULL)
			is->is_pic->pic_reprogram_pin(is);
	}
	sx_xunlock(&intrsrc_lock);
}