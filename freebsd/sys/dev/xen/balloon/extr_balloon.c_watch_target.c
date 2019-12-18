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
struct xs_watch {int dummy; } ;

/* Variables and functions */
 unsigned long long KB_TO_PAGE_SHIFT ; 
 int /*<<< orphan*/  XST_NIL ; 
 int /*<<< orphan*/  set_new_target (unsigned long long) ; 
 int xs_scanf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *,char*,unsigned long long*) ; 

__attribute__((used)) static void 
watch_target(struct xs_watch *watch,
	     const char **vec, unsigned int len)
{
	unsigned long long new_target;
	int err;

	err = xs_scanf(XST_NIL, "memory", "target", NULL,
	    "%llu", &new_target);
	if (err) {
		/* This is ok (for domain0 at least) - so just return */
		return;
	} 
        
	/*
	 * The given memory/target value is in KiB, so it needs converting to
	 * pages.  PAGE_SHIFT converts bytes to pages, hence PAGE_SHIFT - 10.
	 */
	set_new_target(new_target >> KB_TO_PAGE_SHIFT);
}