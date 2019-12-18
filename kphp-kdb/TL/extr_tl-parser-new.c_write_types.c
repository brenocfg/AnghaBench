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
 int /*<<< orphan*/  MAGIC ; 
 int /*<<< orphan*/  TLS_SCHEMA ; 
 int /*<<< orphan*/  TLS_SCHEMA_V2 ; 
 int __f ; 
 scalar_t__ num ; 
 int schema_version ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_function_tree ; 
 int /*<<< orphan*/  tl_type_tree ; 
 int /*<<< orphan*/  total_constructors_num ; 
 int /*<<< orphan*/  total_functions_num ; 
 int /*<<< orphan*/  total_types_num ; 
 int /*<<< orphan*/  tree_act_tl_constructor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_act_tl_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_function ; 
 int /*<<< orphan*/  write_type ; 
 int /*<<< orphan*/  write_type_constructors ; 

void write_types (int f) {
  __f = f;
  if (schema_version == 1) {
    wint (TLS_SCHEMA);
  } else if (schema_version == 2) {
    wint (TLS_SCHEMA_V2);
  } else {
    wint (MAGIC);
  }
  if (schema_version >= 1) {
    wint (0);
    wint (time (0));
  }
  num = 0;
  if (schema_version >= 1) {
    wint (total_types_num);
  }
  tree_act_tl_type (tl_type_tree, write_type);
  if (schema_version >= 1) {
    wint (total_constructors_num);
  }
  tree_act_tl_type (tl_type_tree, write_type_constructors);
  if (schema_version >= 1) {
    wint (total_functions_num);
  }
  tree_act_tl_constructor (tl_function_tree, write_function);
}