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
typedef  int /*<<< orphan*/  each_ref_fn ;

/* Variables and functions */
 unsigned int DO_FOR_EACH_INCLUDE_BROKEN ; 
 int do_for_each_ref (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,void*) ; 
 int /*<<< orphan*/  get_main_ref_store (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_repository ; 

int for_each_fullref_in(const char *prefix, each_ref_fn fn, void *cb_data, unsigned int broken)
{
	unsigned int flag = 0;

	if (broken)
		flag = DO_FOR_EACH_INCLUDE_BROKEN;
	return do_for_each_ref(get_main_ref_store(the_repository),
			       prefix, fn, 0, flag, cb_data);
}