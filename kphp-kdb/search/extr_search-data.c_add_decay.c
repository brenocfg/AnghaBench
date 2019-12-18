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
struct TYPE_2__ {int p; double weight; } ;

/* Variables and functions */
 double M_LN2 ; 
 TYPE_1__ QRT ; 
 scalar_t__ QRT_min_creation_time ; 
 scalar_t__ now ; 

void add_decay (int rate_type, double weight) {
  QRT.p = rate_type;
  QRT.weight = -(M_LN2 / weight);
  QRT_min_creation_time = now - weight * 40;
}