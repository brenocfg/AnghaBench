#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  push_spec ;
struct TYPE_4__ {int /*<<< orphan*/  specs; } ;
typedef  TYPE_1__ git_push ;

/* Variables and functions */
 scalar_t__ git_vector_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_refspec (TYPE_1__*,int /*<<< orphan*/ **,char const*) ; 

int git_push_add_refspec(git_push *push, const char *refspec)
{
	push_spec *spec;

	if (parse_refspec(push, &spec, refspec) < 0 ||
	    git_vector_insert(&push->specs, spec) < 0)
		return -1;

	return 0;
}