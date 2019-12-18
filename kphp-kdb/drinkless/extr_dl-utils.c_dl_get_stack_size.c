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
 scalar_t__ dl_cur_stack () ; 
 scalar_t__ stack_bottom_ptr ; 

size_t dl_get_stack_size() {
  size_t res = (char *)dl_cur_stack() - (char *)stack_bottom_ptr;
  return -res;
}