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
struct TYPE_3__ {struct TYPE_3__* right; struct TYPE_3__* left; int /*<<< orphan*/  x1; } ;
typedef  TYPE_1__ rev_friends_t ;

/* Variables and functions */
 int /*<<< orphan*/  writeout (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  writeout_char (int) ; 

__attribute__((used)) static void dump_rev_friends (rev_friends_t *T) {
  if (T) {
    writeout_char (4);
  } else {
    writeout_char (3);
    return;
  }
  writeout (&T->x1, 16);
  dump_rev_friends (T->left);
  dump_rev_friends (T->right);
}