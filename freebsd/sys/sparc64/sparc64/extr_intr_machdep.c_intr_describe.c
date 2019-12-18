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
struct intr_vector {TYPE_1__* iv_event; } ;
struct TYPE_2__ {int /*<<< orphan*/  ie_fullname; } ;

/* Variables and functions */
 int EINVAL ; 
 int IV_MAX ; 
 int intr_event_describe_handler (TYPE_1__*,void*,char const*) ; 
 int /*<<< orphan*/  intr_table_lock ; 
 struct intr_vector* intr_vectors ; 
 int /*<<< orphan*/  intrcnt_updatename (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
intr_describe(int vec, void *ih, const char *descr)
{
	struct intr_vector *iv;
	int error;

	if (vec < 0 || vec >= IV_MAX)
		return (EINVAL);
	sx_xlock(&intr_table_lock);
	iv = &intr_vectors[vec];
	if (iv == NULL) {
		sx_xunlock(&intr_table_lock);
		return (EINVAL);
	}
	error = intr_event_describe_handler(iv->iv_event, ih, descr);
	if (error) {
		sx_xunlock(&intr_table_lock);
		return (error);
	}
	intrcnt_updatename(vec, iv->iv_event->ie_fullname, 0);
	sx_xunlock(&intr_table_lock);
	return (error);
}