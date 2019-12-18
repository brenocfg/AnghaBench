#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct udp_target_set {int state; int T_count; struct udp_target* last; struct udp_target* S; int /*<<< orphan*/  T; int /*<<< orphan*/  pid; int /*<<< orphan*/  utime; } ;
struct TYPE_3__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  utime; } ;
struct udp_target {TYPE_1__ PID; } ;
struct process_id {int /*<<< orphan*/  pid; int /*<<< orphan*/  utime; } ;
struct TYPE_4__ {struct udp_target* x; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  tree_clear_udp_target_by_fpid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_delete_udp_target_by_fpid (int /*<<< orphan*/ ,struct udp_target*) ; 
 TYPE_2__* tree_get_min_udp_target_by_fpid (int /*<<< orphan*/ ) ; 
 struct udp_target** tree_lookup_value_udp_target_by_fpid (int /*<<< orphan*/ ,void*) ; 
 struct udp_target_set** tree_lookup_value_udp_target_set (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  udp_target_free (struct udp_target*) ; 
 int /*<<< orphan*/  udp_target_set_tree ; 

void udp_target_delete_by_pid (struct process_id *pid) {
  struct udp_target_set **_S = tree_lookup_value_udp_target_set (udp_target_set_tree, (void *)pid);
  if (!_S) { return; }
  struct udp_target_set *ST = *_S;
  switch (ST->state) {
  case 0:
    return;
  case 1:
    if (ST->utime == pid->utime && ST->pid == pid->pid) {
      ST->state = 0;
    }
    return;
  case 2:
    if (ST->S->PID.utime == pid->utime && ST->S->PID.pid == pid->pid) {
      udp_target_free (ST->S);
      ST->state = 0;
    }
    return;
  case 3:
    {
      int ok = ST->last->PID.utime != pid->utime || ST->last->PID.pid != pid->pid;

      struct udp_target **_S = tree_lookup_value_udp_target_by_fpid (ST->T, (void *)pid);
      if (_S) {
        struct udp_target *S = *_S;

        assert (ST->T_count >= 2);
        ST->T = tree_delete_udp_target_by_fpid (ST->T, S);
        ST->T_count --;
        udp_target_free (S);
        
        S = tree_get_min_udp_target_by_fpid (ST->T)->x;

        if (ST->T_count == 1) {
          tree_clear_udp_target_by_fpid (ST->T);
          ST->state = 2;
          ST->S = S;
        } else {
          if (!ok) { 
            ST->last = S;
          }
        }
      }
      return;
    }
  default:
    assert (0);
    return;
    
  }

}