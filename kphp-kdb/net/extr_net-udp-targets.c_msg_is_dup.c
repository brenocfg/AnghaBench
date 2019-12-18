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
struct udp_target {int received_prefix; int /*<<< orphan*/  received_tree; } ;

/* Variables and functions */
 scalar_t__ tree_lookup_int (int /*<<< orphan*/ ,int) ; 

int msg_is_dup (struct udp_target *S, int x) {
  return (x <= S->received_prefix || tree_lookup_int (S->received_tree, x));
}