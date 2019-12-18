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
struct intr_vector {scalar_t__ iv_refcnt; } ;

/* Variables and functions */
 int EINVAL ; 
 int IV_MAX ; 
 int /*<<< orphan*/  PIL_LOW ; 
 int intr_event_remove_handler (void*) ; 
 int /*<<< orphan*/  intr_fast ; 
 int /*<<< orphan*/  intr_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct intr_vector*) ; 
 int /*<<< orphan*/  intr_stray_vector ; 
 int /*<<< orphan*/  intr_table_lock ; 
 struct intr_vector* intr_vectors ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
inthand_remove(int vec, void *cookie)
{
	struct intr_vector *iv;
	int error;

	if (vec < 0 || vec >= IV_MAX)
		return (EINVAL);
	error = intr_event_remove_handler(cookie);
	if (error == 0) {
		/*
		 * XXX: maybe this should be done regardless of whether
		 * intr_event_remove_handler() succeeded?
		 */
		sx_xlock(&intr_table_lock);
		iv = &intr_vectors[vec];
		iv->iv_refcnt--;
		if (iv->iv_refcnt == 0) {
			/*
			 * Don't disable the interrupt for now, so that
			 * stray interrupts get detected...
			 */
			intr_setup(PIL_LOW, intr_fast, vec,
			    intr_stray_vector, iv);
		}
		sx_xunlock(&intr_table_lock);
	}
	return (error);
}