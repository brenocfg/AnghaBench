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
struct TYPE_4__ {struct TYPE_4__* right; struct TYPE_4__* left; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ privacy_t ;

/* Variables and functions */
 scalar_t__ compute_privacy_size (TYPE_1__*) ; 
 int /*<<< orphan*/  writeout (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  writeout_char (int) ; 

__attribute__((used)) static void dump_privacy_tree (privacy_t *T) {
  if (T) {
    writeout_char (3);
  } else {
    writeout_char (2);
    return;
  }
  writeout (&T->x, compute_privacy_size (T) - 2 * sizeof (privacy_t *));
  dump_privacy_tree (T->left);
  dump_privacy_tree (T->right);
}