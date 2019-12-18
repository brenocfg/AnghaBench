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
typedef  int /*<<< orphan*/  uint16_t ;
struct iter_hints {int /*<<< orphan*/  tree; } ;

/* Variables and functions */
 int name_tree_next_root (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int hints_next_root(struct iter_hints* hints, uint16_t* qclass)
{
	return name_tree_next_root(&hints->tree, qclass);
}