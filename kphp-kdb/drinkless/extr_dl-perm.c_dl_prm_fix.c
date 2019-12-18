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
typedef  TYPE_1__* dl_prm_ptr ;
struct TYPE_3__ {struct TYPE_3__* p; int /*<<< orphan*/  r; int /*<<< orphan*/  l; scalar_t__ a; scalar_t__ b; scalar_t__ len; } ;

/* Variables and functions */
 scalar_t__ LEN (int /*<<< orphan*/ ) ; 

void dl_prm_fix (dl_prm_ptr t) {
  while (t != NULL) {
    t->len = t->b - t->a + LEN(t->l) + LEN(t->r);
    t = t->p;
  }
}