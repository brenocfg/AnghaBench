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
struct TYPE_2__ {int* std_val; } ;

/* Variables and functions */
 TYPE_1__** eq ; 
 size_t eq_l ; 
 scalar_t__ eq_n ; 
 int now ; 

int get_time (void) {
  if (eq_n) {
    return eq[eq_l]->std_val[0];
  }
  return now;
}