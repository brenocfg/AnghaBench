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
struct TYPE_3__ {int n; int /*<<< orphan*/ * it; } ;
typedef  TYPE_1__ uni_iterator ;

/* Variables and functions */
 scalar_t__ data_iter_has (int /*<<< orphan*/ *,int) ; 

int uni_iter_has (uni_iterator *it, int val) {
  int i;

  for (i = 0; i < it->n; i++) {
    if (data_iter_has (&it->it[i], val)) {
      return 1;
    }
  }

  return 0;
}