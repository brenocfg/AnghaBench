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
struct TYPE_3__ {int* x; int i; int val; } ;
typedef  TYPE_1__ blist_iterator ;

/* Variables and functions */

void blist_iter_next (blist_iterator *it) {
  if (it->x != NULL && it->i + 1 <= it->x[0]) {
    it->val = it->x[++it->i];
  } else {
    it->val = 0;
  }
}