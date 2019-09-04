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
struct tree {int /*<<< orphan*/  object; } ;
struct rev_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_pending_object (struct rev_info*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void add_pending_tree(struct rev_info *revs, struct tree *tree)
{
	add_pending_object(revs, &tree->object, "");
}