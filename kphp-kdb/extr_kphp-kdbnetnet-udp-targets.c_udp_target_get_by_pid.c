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
struct udp_target_set {int state; int /*<<< orphan*/  T; struct udp_target* last; struct udp_target* S; } ;
struct TYPE_2__ {int /*<<< orphan*/  utime; int /*<<< orphan*/  pid; } ;
struct udp_target {TYPE_1__ PID; } ;
struct process_id {int /*<<< orphan*/  utime; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int matches_pid (TYPE_1__*,struct process_id*) ; 
 struct udp_target** tree_lookup_value_udp_target_by_fpid (int /*<<< orphan*/ ,void*) ; 
 struct udp_target_set** tree_lookup_value_udp_target_set (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  udp_target_set_expand (struct udp_target_set*) ; 
 int /*<<< orphan*/  udp_target_set_tree ; 

struct udp_target *udp_target_get_by_pid (struct process_id *PID) {
  struct udp_target_set **_S = tree_lookup_value_udp_target_set (udp_target_set_tree, (void *)PID);
  if (!_S) { return 0; }
  struct udp_target_set *ST = *_S;
  struct udp_target *S;
  struct udp_target **SS;
  switch (ST->state) {
  case 0:
    return 0;
  case 1:
    udp_target_set_expand (ST);
  case 2:
    S = ST->S;
    if (!PID->pid && !PID->utime) {
      return S;
    } else if (!S->PID.pid && !S->PID.utime) {
      return S;
    } else if (matches_pid (&S->PID, PID) == 2) {    
      return S;
    } else {
      return 0;
    }
  case 3:
    if (!PID->pid && !PID->utime) {
      return ST->last;
    } else {
      SS = tree_lookup_value_udp_target_by_fpid (ST->T, (void *)PID);
      return SS ? *SS : 0;
    }
  default:
    assert (0);
    return 0;
  }
}