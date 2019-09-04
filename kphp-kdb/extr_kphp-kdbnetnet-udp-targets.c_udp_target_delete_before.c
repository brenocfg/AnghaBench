#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct udp_target_set {int state; int utime; int T_count; struct tree_udp_target_by_fpid* T; TYPE_3__* last; struct udp_target* S; } ;
struct TYPE_5__ {int utime; } ;
struct udp_target {TYPE_1__ PID; } ;
struct tree_udp_target_by_fpid {struct udp_target* x; } ;
struct process_id {int utime; int /*<<< orphan*/  pid; } ;
struct TYPE_8__ {TYPE_3__* x; } ;
struct TYPE_6__ {int utime; } ;
struct TYPE_7__ {TYPE_2__ PID; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  tree_act_udp_target_by_fpid (struct tree_udp_target_by_fpid*,int /*<<< orphan*/  (*) (struct udp_target*)) ; 
 int /*<<< orphan*/  tree_clear_udp_target_by_fpid (struct tree_udp_target_by_fpid*) ; 
 int tree_count_udp_target_by_fpid (struct tree_udp_target_by_fpid*) ; 
 TYPE_4__* tree_get_min_udp_target_by_fpid (struct tree_udp_target_by_fpid*) ; 
 struct udp_target_set** tree_lookup_value_udp_target_set (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  tree_split_udp_target_by_fpid (struct tree_udp_target_by_fpid**,struct tree_udp_target_by_fpid**,struct tree_udp_target_by_fpid*,void*) ; 
 int /*<<< orphan*/  udp_target_free (struct udp_target*) ; 
 int /*<<< orphan*/  udp_target_set_tree ; 

void udp_target_delete_before (struct process_id *pid, int utime) {
  struct udp_target_set **_S = tree_lookup_value_udp_target_set (udp_target_set_tree, (void *)pid);
  if (!_S) { return; }
  struct udp_target_set *ST = *_S;
  switch (ST->state) {
  case 0:
    return;
  case 1:
    if (ST->utime < utime) {
      ST->state = 0;
    }
    return;
  case 2:
    if (ST->S->PID.utime < utime && ST->S->PID.utime) {
      udp_target_free (ST->S);
      ST->state = 0;
    }
    return;
  case 3:
    {
      int ok = ST->last->PID.utime < utime;
      struct tree_udp_target_by_fpid *L, *R;
      struct process_id P;
      P.utime = utime ;
      P.pid = 0;
      tree_split_udp_target_by_fpid (&L, &R, ST->T, (void *)&P);
      ST->T = R;
      ST->T_count -= tree_count_udp_target_by_fpid (L);
      tree_act_udp_target_by_fpid (L, udp_target_free);
      tree_clear_udp_target_by_fpid (L);

      assert (ST->T_count >= 0);
      if (ST->T_count == 0) {
        ST->state = 0;
      } else if (ST->T_count == 1) {
        struct udp_target *S = ST->T->x;
        tree_clear_udp_target_by_fpid (ST->T);
        ST->state = 2;
        ST->S = S; 
      } else {
        if (ok) {
          ST->last = tree_get_min_udp_target_by_fpid (ST->T)->x;
        }
      }
      return;
    }
  default:
    assert (0);
    return;
    
  }
}