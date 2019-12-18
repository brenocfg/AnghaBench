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
struct intr_event {int ie_flags; } ;
typedef  enum intr_type { ____Placeholder_intr_type } intr_type ;
typedef  int /*<<< orphan*/  driver_intr_t ;

/* Variables and functions */
 int EINVAL ; 
 int IE_SOFT ; 
 int INTR_ENTROPY ; 
 int /*<<< orphan*/  PI_SWI (int) ; 
 int intr_event_add_handler (struct intr_event*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int,void**) ; 
 int intr_event_create (struct intr_event**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  swi_assign_cpu ; 

int
swi_add(struct intr_event **eventp, const char *name, driver_intr_t handler,
	    void *arg, int pri, enum intr_type flags, void **cookiep)
{
	struct intr_event *ie;
	int error;

	if (flags & INTR_ENTROPY)
		return (EINVAL);

	ie = (eventp != NULL) ? *eventp : NULL;

	if (ie != NULL) {
		if (!(ie->ie_flags & IE_SOFT))
			return (EINVAL);
	} else {
		error = intr_event_create(&ie, NULL, IE_SOFT, 0,
		    NULL, NULL, NULL, swi_assign_cpu, "swi%d:", pri);
		if (error)
			return (error);
		if (eventp != NULL)
			*eventp = ie;
	}
	error = intr_event_add_handler(ie, name, NULL, handler, arg,
	    PI_SWI(pri), flags, cookiep);
	return (error);
}