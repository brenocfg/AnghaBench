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
typedef  int /*<<< orphan*/  dl_trp_node ;

/* Variables and functions */
 int allocated_nodes_cnt ; 

size_t dl_trp_get_memory (void) {
  return allocated_nodes_cnt * sizeof (dl_trp_node);
}