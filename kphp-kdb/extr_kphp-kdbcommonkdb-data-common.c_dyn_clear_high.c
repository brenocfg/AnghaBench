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
 scalar_t__ dyn_last ; 
 scalar_t__ dyn_mark_top ; 
 scalar_t__ dyn_top ; 

void dyn_clear_high (void) {
  dyn_top = dyn_mark_top ? dyn_mark_top : dyn_last;
}