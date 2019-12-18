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
 int FN ; 
 scalar_t__ map_int_int_get_memory_used (int /*<<< orphan*/ *) ; 
 scalar_t__ map_ll_int_get_memory_used (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * q_st_int ; 
 int /*<<< orphan*/ * q_st_ll ; 
 scalar_t__* std_t ; 

long get_q_st_memory (void) {
  long res = 0;
  int i;
  for (i = 0; i < FN; i++) {
    if (std_t[i]) {
      res += map_ll_int_get_memory_used (&q_st_ll[i]);
    } else {
      res += map_int_int_get_memory_used (&q_st_int[i]);
    }
  }
  return res;
}