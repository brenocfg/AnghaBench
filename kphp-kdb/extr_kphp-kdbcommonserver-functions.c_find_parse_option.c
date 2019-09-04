#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int val; scalar_t__ name; } ;

/* Variables and functions */
 TYPE_1__* global_longopts ; 

int find_parse_option (int val) {
  int s = 0;
  while (global_longopts[s].name || global_longopts[s].val) { 
    if (global_longopts[s].val == val) { return s; }
    s ++;
  }
  return -1;
}