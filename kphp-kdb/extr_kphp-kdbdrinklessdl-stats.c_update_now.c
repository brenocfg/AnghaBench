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
 double CLOCKS_PER_SEC ; 
 scalar_t__ clock () ; 
 double precise_now ; 

void update_now() {
  precise_now = (double)clock() / CLOCKS_PER_SEC;
}