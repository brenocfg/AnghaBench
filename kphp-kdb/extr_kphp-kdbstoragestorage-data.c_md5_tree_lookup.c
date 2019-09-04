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
struct TYPE_4__ {struct TYPE_4__* right; struct TYPE_4__* left; int /*<<< orphan*/ * x; } ;
typedef  TYPE_1__ md5_tree_t ;

/* Variables and functions */
 int memcmp (unsigned char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static md5_tree_t *md5_tree_lookup (md5_tree_t *T, unsigned char x[16]) {
  while (T) {
    int c = memcmp (&x[0], &T->x[0], 16);
    if (c < 0) {
      T = T->left;
    } else if (c > 0) {
      T = T->right;
    } else {
      return T;
    }
  }
  return T;
}