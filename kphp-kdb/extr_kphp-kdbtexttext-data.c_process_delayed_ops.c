#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user_t ;
struct TYPE_4__ {int flags; int clear_mask; int set_mask; struct TYPE_4__* right; int /*<<< orphan*/  x; struct TYPE_4__* left; } ;
typedef  TYPE_1__ tree_t ;

/* Variables and functions */
 scalar_t__ adjust_message_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  zfree (TYPE_1__*,int) ; 

__attribute__((used)) static void process_delayed_ops (user_t *U, tree_t *T) {
  if (!T) {
    return;
  }
  process_delayed_ops (U, T->left);
  if (T->flags == -1) {
    assert (adjust_message_internal (U, 0, T->x, -1, -1) >= 0);
  } else {
    assert (adjust_message_internal (U, 0, T->x, T->clear_mask, T->set_mask) >= 0);
  }
  process_delayed_ops (U, T->right);
  zfree (T, sizeof (tree_t));
}