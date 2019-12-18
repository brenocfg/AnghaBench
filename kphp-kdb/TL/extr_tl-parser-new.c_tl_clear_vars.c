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
 scalar_t__* last_num_var ; 
 size_t namespace_level ; 
 int /*<<< orphan*/  tl_del_var ; 
 int /*<<< orphan*/  tree_act_tl_var (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_clear_tl_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vars ; 

void tl_clear_vars (void) {
  tree_act_tl_var (vars[namespace_level], tl_del_var);
  vars[namespace_level] = tree_clear_tl_var (vars[namespace_level]);
  last_num_var[namespace_level] = 0;
}