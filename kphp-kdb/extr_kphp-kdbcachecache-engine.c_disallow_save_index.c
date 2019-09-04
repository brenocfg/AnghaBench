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
 int /*<<< orphan*/  kprintf (char*) ; 

int disallow_save_index (int writing_binlog) {
  kprintf ("Writing index without counters ([-D 16] command line mode) is forbidden. Run cache-engine with [-A] option for allowing this action.\n");
  return -1;
}