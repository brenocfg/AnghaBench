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
 scalar_t__ GH_N ; 
 int GH_mode ; 
 scalar_t__ GH_n ; 
 scalar_t__ GH_total ; 

void clear_gather_heap (int mode) {
  GH_N = 0;
  GH_total = 0;
  GH_mode = mode;
  GH_n = 0;
}