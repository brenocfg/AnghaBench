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
struct TYPE_2__ {scalar_t__ T; } ;

/* Variables and functions */
 TYPE_1__* TAT ; 
 int amortization_counter_types ; 
 double fabs (scalar_t__) ; 

__attribute__((used)) static int get_acounter_id_by_t (int T) {
  int i;
  for (i = 0; i < amortization_counter_types; i++) {
    if (fabs (TAT[i].T - T) < 0.5) {
      return i;
    }
  }
  return -1;
}