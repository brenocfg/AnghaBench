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
struct tl_tree {int dummy; } ;

/* Variables and functions */
 struct tl_tree** __vars ; 
 struct tl_tree** last_var_ptr ; 

struct tl_tree **get_var_space (struct tl_tree **vars, int n) {
//  fprintf (stderr, "get_var_space: %d\n", n);
  if (vars - n < __vars) { return 0; }
  if (last_var_ptr > vars - n) {
    last_var_ptr = vars - n;
  }
  return vars - n;
}