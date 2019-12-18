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
struct user_groups {int cur_groups; int* G; } ;
struct user {struct user_groups* grp; } ;

/* Variables and functions */

int is_user_in_group (struct user *U, int group_id) {
  struct user_groups *G = U->grp;
  if (G) {
    int l = -1, r = G->cur_groups;
    while (r - l > 1) {
      int m = (l + r) >> 1;
      if (group_id < G->G[m]) {
	r = m;
      } else {
	l = m;
      }
    }
  
    if (l >= 0 && G->G[l] == group_id) {
      return 1;
    }
  }
  return 0;
}