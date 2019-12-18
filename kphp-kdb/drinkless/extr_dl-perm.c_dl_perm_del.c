#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* dl_prm_ptr ;
struct TYPE_18__ {int len; int /*<<< orphan*/  rv; TYPE_1__* v; } ;
typedef  TYPE_2__ dl_perm ;
struct TYPE_17__ {int /*<<< orphan*/  a; } ;

/* Variables and functions */
 scalar_t__ LEN (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dl_free_prm (TYPE_1__*) ; 
 int /*<<< orphan*/  dl_prm_extract (TYPE_1__*,TYPE_1__**,TYPE_1__**,TYPE_1__**,int) ; 
 int /*<<< orphan*/  dl_prm_merge (TYPE_1__**,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* dl_prm_rev_del (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dl_prm_split_node (TYPE_1__*,TYPE_1__**,TYPE_1__**,int,int /*<<< orphan*/ *) ; 

int dl_perm_del (dl_perm *pp, int i) {
  if (!(0 <= i && i < pp->len)) {
    return -1;
  }

//  fprintf (stderr, "DeL %d\n", i);

  dl_prm_ptr p[6] = {NULL}, add;
  dl_prm_extract (pp->v, &p[0], &p[3], &p[1], i);
  i -= LEN(p[0]);

  dl_prm_split_node (p[1], &p[1], &add, i, &pp->rv);
  dl_prm_split_node (add, &add, &p[2], 1, &pp->rv);

  int s;
  for (s = 0; s < 3; s++) {
    dl_prm_merge (&p[s + 1], p[s], p[s + 1], &pp->rv);
  }

  pp->v = p[3];

  assert (dl_prm_rev_del (&pp->rv, add->a) == add);
  dl_free_prm (add);
  pp->len--;

  return 0;
}