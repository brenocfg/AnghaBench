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
 long max_allocated_data ; 
 long max_loaded_index_data ; 

void set_memory_limit (long max_memory) {
  max_loaded_index_data = max_memory >> 1;
  max_allocated_data = max_memory >> 1;
}