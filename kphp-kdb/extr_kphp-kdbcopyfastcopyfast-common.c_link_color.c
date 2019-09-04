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
 int check_common_rule (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/ * network ; 
 int rules_num ; 

int link_color (unsigned ip1, unsigned ip2) {
  int i;
  int best = 0;
  for (i = 0; i < rules_num; i++) {
    int r = check_common_rule (&network[i], ip1, ip2);
    if (r == 2) {
      return 2;
    }
    if (r == 1) {
      best = 1;
    }
  }
  return best;
}