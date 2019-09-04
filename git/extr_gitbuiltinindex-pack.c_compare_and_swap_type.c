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
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int /*<<< orphan*/  type_cas_lock () ; 
 int /*<<< orphan*/  type_cas_unlock () ; 

__attribute__((used)) static int compare_and_swap_type(signed char *type,
				 enum object_type want,
				 enum object_type set)
{
	enum object_type old;

	type_cas_lock();
	old = *type;
	if (old == want)
		*type = set;
	type_cas_unlock();

	return old == want;
}