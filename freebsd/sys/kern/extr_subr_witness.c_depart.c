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
struct witness {scalar_t__ w_refcount; scalar_t__ w_line; int /*<<< orphan*/ * w_file; TYPE_1__* w_class; } ;
struct TYPE_2__ {int lc_flags; } ;

/* Variables and functions */
 int LC_SLEEPLOCK ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  w_sleep_cnt ; 
 int /*<<< orphan*/  w_spin_cnt ; 
 int /*<<< orphan*/  witness_increment_graph_generation () ; 

__attribute__((used)) static void
depart(struct witness *w)
{

	MPASS(w->w_refcount == 0);
	if (w->w_class->lc_flags & LC_SLEEPLOCK) {
		w_sleep_cnt--;
	} else {
		w_spin_cnt--;
	}
	/*
	 * Set file to NULL as it may point into a loadable module.
	 */
	w->w_file = NULL;
	w->w_line = 0;
	witness_increment_graph_generation();
}