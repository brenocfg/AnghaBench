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
typedef  int /*<<< orphan*/ * dyn_mark_t ;

/* Variables and functions */
 int /*<<< orphan*/  dyn_cur ; 
 int /*<<< orphan*/  dyn_mark_bottom ; 
 int /*<<< orphan*/  dyn_mark_top ; 
 int /*<<< orphan*/  dyn_top ; 

void dyn_mark (dyn_mark_t dyn_state) {
  if (dyn_state) {
    dyn_state[0] = dyn_mark_bottom;
    dyn_state[1] = dyn_mark_top;
  }
  dyn_mark_bottom = dyn_cur;
  dyn_mark_top = dyn_top;
}