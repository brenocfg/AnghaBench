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
struct netrule {int type; int level1; int level2; } ;

/* Variables and functions */
 scalar_t__ check_rule (struct netrule*,unsigned int) ; 
 struct netrule* network ; 
 int rules_num ; 

int link_level (unsigned ip, int color) {
  if (color == 0) {
    return 32;
  }
  if (color == 1) {
    int i;
    int l = 0;
    for (i = 0; i < rules_num; i++) if (network[i].type == 1) {
      struct netrule *A = &network[i];
      if (check_rule (A, ip) && A->level1 > l) {
        l = A->level1;
      }
    }
    return l;
  }
  if (color == 2) {
    int i;
    int l = 0;
    for (i = 0; i < rules_num; i++) if (network[i].type == 2) {
      struct netrule *A = &network[i];
      if (check_rule (A, ip) && A->level2 > l) {
        l = A->level2;
      }
    }
    return l;
  }
  return 0;
}