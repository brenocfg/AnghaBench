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
struct TYPE_2__ {int /*<<< orphan*/  h_idx; } ;
struct udp_target {int unack_size; int /*<<< orphan*/  confirm_tree; TYPE_1__ confirm_timer; } ;

/* Variables and functions */
 int START_WINDOW_SIZE ; 
 int /*<<< orphan*/  lrand48 () ; 
 int /*<<< orphan*/  start_confirm_timer (struct udp_target*) ; 
 int /*<<< orphan*/  tree_insert_int (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_lookup_int (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udp_confirms_send (struct udp_target*) ; 

void add_force_confirm (struct udp_target *S, int x) {
  if (!S->confirm_timer.h_idx) {
    start_confirm_timer (S);
  }
  if (!tree_lookup_int (S->confirm_tree, x)) {
    S->confirm_tree = tree_insert_int (S->confirm_tree, x, lrand48 ());
    S->unack_size ++;
    if (S->unack_size >= START_WINDOW_SIZE / 2000) {
      udp_confirms_send (S);
    }
  }
}