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
struct TYPE_3__ {int mx; scalar_t__ rn; scalar_t__ n; int /*<<< orphan*/  mem; } ;
typedef  TYPE_1__ vector ;

/* Variables and functions */
 int /*<<< orphan*/  qmalloc (int) ; 

void vct_init (vector *v) {
  v->mem = qmalloc (sizeof (int));
  v->mx = 1, v->n = 0;
  v->rn = 0;
}