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
typedef  int /*<<< orphan*/  node ;

/* Variables and functions */
 int /*<<< orphan*/ * dl_malloc0 (int) ; 

inline node *new_node (void) {
  return dl_malloc0 (sizeof (node));
}