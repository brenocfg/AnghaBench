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
 int backtrace (void**,int) ; 
 int max_depth ; 
 int uncounted_depth ; 

int dl_get_stack_depth (void) {
  #define max_depth 50
  #define uncounted_depth 12
  static void *tmp[max_depth];
  int res = backtrace (tmp, max_depth) - uncounted_depth;
  return res < 0 ? 0 : res;
}