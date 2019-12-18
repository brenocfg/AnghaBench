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
struct TYPE_4__ {char* key; scalar_t__ data; } ;
typedef  TYPE_1__ ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  FIND ; 
 scalar_t__ hsearch_r (TYPE_1__,int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isgroup_map ; 

__attribute__((used)) static int
is_a_group(char *name)
{
	ENTRY	 		 item;
	ENTRY			*ret_item;
	
	item.key = name;
	if (hsearch_r(item, FIND, &ret_item, &isgroup_map) == 0)
		return (0);

	return (*(int *)ret_item->data);
}