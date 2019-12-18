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
struct TYPE_3__ {int mx; scalar_t__ n; int /*<<< orphan*/  mem; } ;
typedef  TYPE_1__ vector ;

/* Variables and functions */
 int /*<<< orphan*/  qfree (int /*<<< orphan*/ ,int) ; 

void vct_free (vector *v) {
  qfree (v->mem, sizeof (int) * v->mx);
  v->mx = 0, v->n = 0;
}