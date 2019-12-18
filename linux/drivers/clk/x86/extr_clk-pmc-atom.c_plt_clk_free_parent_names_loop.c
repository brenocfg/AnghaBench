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

/* Variables and functions */
 int /*<<< orphan*/  kfree (char const**) ; 
 int /*<<< orphan*/  kfree_const (char const*) ; 

__attribute__((used)) static void plt_clk_free_parent_names_loop(const char **parent_names,
					   unsigned int i)
{
	while (i--)
		kfree_const(parent_names[i]);
	kfree(parent_names);
}