#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct user_groups* grp; } ;
typedef  TYPE_1__ user_t ;
struct user_groups {int cur_groups; int /*<<< orphan*/  G; } ;

/* Variables and functions */
 int MAX_USERS ; 
 int /*<<< orphan*/  R ; 
 int R_cnt ; 
 TYPE_1__* get_user (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int get_user_groups (int user_id) {
  user_t *U = get_user (user_id);
  if (!U || !U->grp) {
    R_cnt = 0;
    return 0;
  }
  struct user_groups *G = U->grp;
  int cnt = G->cur_groups;
  R_cnt = (cnt > MAX_USERS ? MAX_USERS : cnt);
  memcpy (R, G->G, R_cnt * 4);
  return cnt;
}