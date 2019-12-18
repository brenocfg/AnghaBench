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
struct TYPE_2__ {scalar_t__ obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_ANY ; 
 int /*<<< orphan*/  check_object (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int nr_objects ; 
 TYPE_1__* obj_list ; 

__attribute__((used)) static void write_rest(void)
{
	unsigned i;
	for (i = 0; i < nr_objects; i++) {
		if (obj_list[i].obj)
			check_object(obj_list[i].obj, OBJ_ANY, NULL, NULL);
	}
}