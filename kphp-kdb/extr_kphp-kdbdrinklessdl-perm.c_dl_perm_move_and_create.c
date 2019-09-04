#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* dl_prm_ptr ;
struct TYPE_19__ {int n; int len; TYPE_1__* v; int /*<<< orphan*/  rv; } ;
typedef  TYPE_2__ dl_perm ;
struct TYPE_18__ {int a; int b; int len; int /*<<< orphan*/  y; } ;

/* Variables and functions */
 scalar_t__ LEN (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* dl_alloc_prm () ; 
 int dl_perm_get_rev_i (TYPE_2__*,int) ; 
 int /*<<< orphan*/  dl_prm_extract (TYPE_1__*,TYPE_1__**,TYPE_1__**,TYPE_1__**,int) ; 
 int /*<<< orphan*/  dl_prm_merge (TYPE_1__**,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dl_prm_rev_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dl_prm_split_node (TYPE_1__*,TYPE_1__**,TYPE_1__**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rand () ; 

int dl_perm_move_and_create (dl_perm *pp, int id, int i) {
  if (!(0 <= id && id < pp->n)) {
    return -1;
  }
  if (!(0 <= i && i <= pp->len)) {
    return -1;
  }
  //TODO: replace "assert" with "return -1"
  assert (dl_perm_get_rev_i (pp, id) == -1);

  //dbg ("dl_perm_move_and_create (id = %d) (i = %d) (len = %d)\n", id, i, pp->len);
  //dl_perm_dbg (pp);

  dl_prm_ptr p[10] = {NULL};
  if (i == pp->len) {
    p[0] = pp->v;
  } else {
    dl_prm_extract (pp->v, &p[0], &p[4], &p[1], i);
    i -= LEN (p[0]);
    dl_prm_split_node (p[1], &p[1], &p[3], i, &pp->rv);
  }

  dl_prm_ptr v = dl_alloc_prm();
  v->a = id;
  v->b = id + 1;
  v->len = v->b - v->a;
  v->y = rand();
  dl_prm_rev_add (&pp->rv, v);

  p[2] = v;

  int s;
  for (s = 0; s < 4; s++) {
    dl_prm_merge (&p[s + 1], p[s], p[s + 1], &pp->rv);
  }

  pp->v = p[4];
  pp->len++;

  return 0;
}