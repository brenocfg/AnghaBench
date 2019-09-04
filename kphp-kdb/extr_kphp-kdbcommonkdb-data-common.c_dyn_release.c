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
typedef  void** dyn_mark_t ;

/* Variables and functions */
 void* dyn_cur ; 
 void* dyn_mark_bottom ; 
 void* dyn_mark_top ; 
 void* dyn_top ; 

void dyn_release (dyn_mark_t dyn_state) {
  dyn_cur = dyn_mark_bottom;
  dyn_top = dyn_mark_top;
  if (dyn_state) {
    dyn_mark_bottom = dyn_state[0];
    dyn_mark_top = dyn_state[1];
  } else {
    dyn_mark_bottom = dyn_mark_top = 0;
  }
}