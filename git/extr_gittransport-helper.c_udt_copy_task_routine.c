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
struct unidirectional_transfer {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ SSTATE_FINISHED ; 
 scalar_t__ STATE_NEEDS_CLOSING (scalar_t__) ; 
 scalar_t__ STATE_NEEDS_READING (scalar_t__) ; 
 scalar_t__ STATE_NEEDS_WRITING (scalar_t__) ; 
 int /*<<< orphan*/  udt_close_if_finished (struct unidirectional_transfer*) ; 
 scalar_t__ udt_do_read (struct unidirectional_transfer*) ; 
 scalar_t__ udt_do_write (struct unidirectional_transfer*) ; 

__attribute__((used)) static void *udt_copy_task_routine(void *udt)
{
	struct unidirectional_transfer *t = (struct unidirectional_transfer *)udt;
	while (t->state != SSTATE_FINISHED) {
		if (STATE_NEEDS_READING(t->state))
			if (udt_do_read(t))
				return NULL;
		if (STATE_NEEDS_WRITING(t->state))
			if (udt_do_write(t))
				return NULL;
		if (STATE_NEEDS_CLOSING(t->state))
			udt_close_if_finished(t);
	}
	return udt;	/* Just some non-NULL value. */
}