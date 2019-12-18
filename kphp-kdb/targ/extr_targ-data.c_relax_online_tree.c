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
 int OLIST_COUNT ; 
 scalar_t__* ocntT ; 

void relax_online_tree (void) {
  long i;
  for (i = OLIST_COUNT - 1; i > 0; i--) {
    ocntT[i] = ocntT[2 * i] + ocntT[2 * i + 1];
  }
}