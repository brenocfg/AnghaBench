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
struct intsrc {int is_handlers; int is_domain; TYPE_1__* is_pic; int /*<<< orphan*/  is_event; } ;
typedef  enum intr_type { ____Placeholder_intr_type } intr_type ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* pic_enable_source ) (struct intsrc*) ;int /*<<< orphan*/  (* pic_enable_intr ) (struct intsrc*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int intr_event_add_handler (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int,void**) ; 
 struct intsrc* intr_lookup_source (int) ; 
 int /*<<< orphan*/  intr_priority (int) ; 
 int /*<<< orphan*/  intrcnt_updatename (struct intsrc*) ; 
 int /*<<< orphan*/  intrsrc_lock ; 
 int /*<<< orphan*/  stub1 (struct intsrc*) ; 
 int /*<<< orphan*/  stub2 (struct intsrc*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
intr_add_handler(const char *name, int vector, driver_filter_t filter,
    driver_intr_t handler, void *arg, enum intr_type flags, void **cookiep,
    int domain)
{
	struct intsrc *isrc;
	int error;

	isrc = intr_lookup_source(vector);
	if (isrc == NULL)
		return (EINVAL);
	error = intr_event_add_handler(isrc->is_event, name, filter, handler,
	    arg, intr_priority(flags), flags, cookiep);
	if (error == 0) {
		sx_xlock(&intrsrc_lock);
		intrcnt_updatename(isrc);
		isrc->is_handlers++;
		if (isrc->is_handlers == 1) {
			isrc->is_domain = domain;
			isrc->is_pic->pic_enable_intr(isrc);
			isrc->is_pic->pic_enable_source(isrc);
		}
		sx_xunlock(&intrsrc_lock);
	}
	return (error);
}