#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* dl_prm_ptr ;
struct TYPE_8__ {int len; int /*<<< orphan*/  rv; int /*<<< orphan*/  v; scalar_t__ n; } ;
typedef  TYPE_2__ dl_perm ;
struct TYPE_7__ {int /*<<< orphan*/  y; scalar_t__ a; scalar_t__ b; scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* dl_alloc_prm () ; 
 int /*<<< orphan*/  dl_prm_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dl_prm_rev_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  rand () ; 
 scalar_t__ unlikely (int) ; 

void dl_perm_inc_pass (dl_perm *p, int n, int pass_n) {
  if (unlikely (n <= 0)) {
    return;
  }
  assert (pass_n <= n);

  if (pass_n == n) {
    p->n += n;
    return;
  }

  dl_prm_ptr v = dl_alloc_prm();
  v->a = p->n + pass_n;
  p->n += n;
  p->len += n - pass_n;
  v->b = p->n;
  v->len = v->b - v->a;
  v->y = rand();
  dl_prm_rev_add (&p->rv, v);
  dl_prm_merge (&p->v, p->v, v, &p->rv);
}