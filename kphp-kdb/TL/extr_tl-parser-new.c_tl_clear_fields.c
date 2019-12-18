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
 int /*<<< orphan*/ * fields ; 
 size_t namespace_level ; 
 int /*<<< orphan*/  tree_clear_tl_field (int /*<<< orphan*/ ) ; 

void tl_clear_fields (void) {
//  tree_act_tl_field (fields[namespace_level], (void *)free); 
  fields[namespace_level] = tree_clear_tl_field (fields[namespace_level]); 
}