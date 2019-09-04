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
struct tl_tree_array {int args_num; int /*<<< orphan*/ * args; } ;

/* Variables and functions */
 int gen_field_fetch (int /*<<< orphan*/ ,void**,int,int*,int,int) ; 
 void* tlsub_ret_ok ; 

int gen_array_fetch (struct tl_tree_array *a, void **IP, int max_size, int *vars) {
  if (max_size <= 10) { return -1; }
  int l = 0;
  if (a->args_num > 1) {
    int i;
    for (i = 0; i < a->args_num; i++) {
      int x = gen_field_fetch (a->args[i], IP + l, max_size - l, vars, i, 0); 
      if (x < 0) { return -1; }
      l += x;
    }
  } else {
    int x = gen_field_fetch (a->args[0], IP + l, max_size - l, vars, 0, 1); 
    if (x < 0) { return -1; }
    l += x;
  }
  if (max_size - l <= 10) { return -1; }
  IP[l ++] = tlsub_ret_ok;
//  c->IP = IP_dup (IP, l);
  return l;
}