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
struct fs_base {int /*<<< orphan*/  name; int /*<<< orphan*/  complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  fs_put (struct fs_base*) ; 
 int /*<<< orphan*/  kfree (struct fs_base*) ; 
 int /*<<< orphan*/  kfree_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fs_remove_node(struct fs_base *node)
{
	fs_put(node);
	wait_for_completion(&node->complete);
	kfree_const(node->name);
	kfree(node);
}