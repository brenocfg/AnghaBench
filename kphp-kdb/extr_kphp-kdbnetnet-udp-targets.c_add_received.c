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
struct udp_target {int received_prefix; scalar_t__ received_tree; } ;
struct TYPE_2__ {int x; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lrand48 () ; 
 int /*<<< orphan*/  start_rx_timer (struct udp_target*) ; 
 int /*<<< orphan*/  stop_rx_timer (struct udp_target*) ; 
 scalar_t__ tree_delete_int (scalar_t__,int) ; 
 TYPE_1__* tree_get_min_int (scalar_t__) ; 
 scalar_t__ tree_insert_int (scalar_t__,int,int /*<<< orphan*/ ) ; 

void add_received (struct udp_target *S, int x) {
  if (x == S->received_prefix + 1) {
    S->received_prefix ++;
    if (S->received_tree) {
      while (S->received_tree) {
        int y = tree_get_min_int (S->received_tree)->x;
        assert (y >= S->received_prefix + 1);
        if (y == S->received_prefix + 1) {
          S->received_tree = tree_delete_int (S->received_tree, y);
          S->received_prefix ++;
        } else {
          break;
        }
      }
      if (!S->received_tree) {
        stop_rx_timer (S);
      }
    }
  } else {
    if (!S->received_tree) {
      start_rx_timer (S);
    }
    S->received_tree = tree_insert_int (S->received_tree, x, lrand48 ());
  }
}