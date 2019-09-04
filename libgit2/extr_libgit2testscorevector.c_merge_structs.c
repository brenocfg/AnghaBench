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
struct TYPE_2__ {scalar_t__ content; int count; } ;
typedef  TYPE_1__ my_struct ;

/* Variables and functions */
 int GIT_EEXISTS ; 
 int /*<<< orphan*/  _struct_count ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  git__free (void*) ; 

__attribute__((used)) static int merge_structs(void **old_raw, void *new)
{
	my_struct *old = *(my_struct **)old_raw;
	cl_assert(((my_struct *)old)->content == ((my_struct *)new)->content);
	((my_struct *)old)->count += 1;
	git__free(new);
	_struct_count--;
	return GIT_EEXISTS;
}