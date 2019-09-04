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
 int copy_mod ; 
 int copy_rem ; 

int positive_counter_fits (int counter_id) {
  if (counter_id <= 0) { return 0; }
  return counter_id % copy_mod == copy_rem;
}