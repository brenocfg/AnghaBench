#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  perm_list ;
struct TYPE_6__ {int n; int len; TYPE_1__* v; } ;
typedef  TYPE_2__ dl_perm_list ;
struct TYPE_5__ {int /*<<< orphan*/  r; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int dl_perm_list_get_rev_i (TYPE_2__*,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_alloc (int,int) ; 
 int /*<<< orphan*/ * move_r (int /*<<< orphan*/ ,int) ; 

int dl_perm_list_move_and_create (dl_perm_list *p, int id, int i) {
  if (!(0 <= id && id < p->n)) {
    return -1;
  }
  if (!(0 <= i && i <= p->len)) {
    return -1;
  }
  //TODO: replace "assert" with "return -1"
  assert (dl_perm_list_get_rev_i (p, id) == -1);

  perm_list *v = move_r (p->v->r, i), *add;
  add = list_alloc (id, id + 1);
  list_add (v, add);

  p->len++;

  return 0;
}