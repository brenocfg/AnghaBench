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
typedef  void tl_tree ;

/* Variables and functions */
 scalar_t__ int_to_var_nat_const_init (int /*<<< orphan*/ ) ; 
 int schema_version ; 
 scalar_t__ tl_parse_error () ; 
 int /*<<< orphan*/  tl_parse_int () ; 
 int /*<<< orphan*/  tl_parse_long () ; 

struct tl_tree *read_num_const (int *var_num) {
  void *res = (void *)int_to_var_nat_const_init (schema_version >= 2 ? tl_parse_int () : tl_parse_long ());
  return tl_parse_error () ? 0 : res;
}