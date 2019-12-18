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
struct dbm_res {int member_0; int /*<<< orphan*/  member_1; } ;

/* Variables and functions */
#define  ITER_ARCH 130 
#define  ITER_MACRO 129 
#define  ITER_NONE 128 
 int iteration ; 
 struct dbm_res page_byarch (int /*<<< orphan*/ *) ; 
 struct dbm_res page_bymacro (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct dbm_res page_bytitle (int,int /*<<< orphan*/ *) ; 

struct dbm_res
dbm_page_next(void)
{
	struct dbm_res			 res = {-1, 0};

	switch(iteration) {
	case ITER_NONE:
		return res;
	case ITER_ARCH:
		return page_byarch(NULL);
	case ITER_MACRO:
		return page_bymacro(0, NULL);
	default:
		return page_bytitle(iteration, NULL);
	}
}