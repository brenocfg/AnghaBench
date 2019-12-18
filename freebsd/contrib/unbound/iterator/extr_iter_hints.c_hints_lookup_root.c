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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct iter_hints_stub {struct delegpt* dp; } ;
struct iter_hints {int /*<<< orphan*/  tree; } ;
struct delegpt {int dummy; } ;

/* Variables and functions */
 scalar_t__ name_tree_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

struct delegpt* 
hints_lookup_root(struct iter_hints* hints, uint16_t qclass)
{
	uint8_t rootlab = 0;
	struct iter_hints_stub *stub;
	stub = (struct iter_hints_stub*)name_tree_find(&hints->tree,
		&rootlab, 1, 1, qclass);
	if(!stub)
		return NULL;
	return stub->dp;
}