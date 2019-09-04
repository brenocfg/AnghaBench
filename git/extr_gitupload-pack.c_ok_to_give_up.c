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
typedef  int /*<<< orphan*/  uint32_t ;
struct object_array {int /*<<< orphan*/  nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_KNOWN ; 
 int /*<<< orphan*/  GENERATION_NUMBER_ZERO ; 
 int /*<<< orphan*/  THEY_HAVE ; 
 int can_all_from_reach_with_flag (struct object_array*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oldest_have ; 

__attribute__((used)) static int ok_to_give_up(const struct object_array *have_obj,
			 struct object_array *want_obj)
{
	uint32_t min_generation = GENERATION_NUMBER_ZERO;

	if (!have_obj->nr)
		return 0;

	return can_all_from_reach_with_flag(want_obj, THEY_HAVE,
					    COMMON_KNOWN, oldest_have,
					    min_generation);
}