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
struct resource_list {int dummy; } ;
typedef  int /*<<< orphan*/  rman_res_t ;

/* Variables and functions */
 int /*<<< orphan*/  resource_list_add (struct resource_list*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * resource_list_find (struct resource_list*,int,int) ; 

int
resource_list_add_next(struct resource_list *rl, int type, rman_res_t start,
    rman_res_t end, rman_res_t count)
{
	int rid;

	rid = 0;
	while (resource_list_find(rl, type, rid) != NULL)
		rid++;
	resource_list_add(rl, type, rid, start, end, count);
	return (rid);
}