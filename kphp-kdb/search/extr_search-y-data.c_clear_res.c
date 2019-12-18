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
 scalar_t__ R_cnt ; 
 scalar_t__ R_tot ; 
 int /*<<< orphan*/  init_order () ; 

void clear_res (void) {
  R_cnt = R_tot = 0;
  init_order ();
}