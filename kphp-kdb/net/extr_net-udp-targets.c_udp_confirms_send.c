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
struct udp_target {scalar_t__ confirm_tree; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_buf_clean () ; 
 int /*<<< orphan*/  out_buf_flush (int) ; 
 int /*<<< orphan*/  out_buf_set_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_buf_set_target (struct udp_target*) ; 

void udp_confirms_send (struct udp_target *S) {
  out_buf_set_mode (S->flags);
  out_buf_set_target (S);
  assert (out_buf_clean ());
  while (S->confirm_tree) {
    out_buf_flush (1);
    assert (out_buf_clean ());
  }
}