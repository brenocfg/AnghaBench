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
typedef  int /*<<< orphan*/ * dl_prm_ptr ;
struct TYPE_3__ {int len; int /*<<< orphan*/ * v; int /*<<< orphan*/  rv; } ;
typedef  TYPE_1__ dl_perm ;

/* Variables and functions */
 int LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dl_prm_extract (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  dl_prm_merge (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dl_prm_split_node (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *) ; 

int dl_perm_move (dl_perm *pp, int i, int j) {
  if (!(0 <= i && i < pp->len)) {
    return -1;
  }
  if (!(0 <= j && j < pp->len)) {
    return -1;
  }
  if (i == j) {
    return 0;
  }

//  fprintf (stderr, "MoVE %d %d\n", i, j);

  dl_prm_ptr p[10] = {NULL}, add;
  dl_prm_extract (pp->v, &p[5], &p[8], &p[6], i);
  i -= LEN(p[5]);
//  fprintf (stderr, "len = %d\n", LEN(p[5]));
//  _go (p[5], 0);

  dl_prm_split_node (p[6], &p[6], &add, i, &pp->rv);
  dl_prm_split_node (add, &add, &p[7], 1, &pp->rv);

  int s;
  for (s = 0; s <= 3; s++) {
    int xn = LEN(p[s + 5]);
    if (j < xn) {
      dl_prm_extract (p[s + 5], &p[s], &p[s + 4], &p[s + 1], j);
      p[s + 5] = NULL;
      j -= LEN(p[s]);
      dl_prm_split_node (p[s + 1], &p[s + 1], &p[s + 3], j, &pp->rv);
      p[s + 2] = add;
      add = NULL;
      break;
    } else {
      j -= xn;
      p[s] = p[s + 5];
      p[s + 5] = NULL;
    }
  }
  p[9] = add;

/*  for (s = 0; s <= 9; s++) {
    fprintf (stderr, "s = %d\n", s);
    _go (p[s], 0);
  }
*/
  for (s = 0; s < 9; s++) {
    dl_prm_merge (&p[s + 1], p[s], p[s + 1], &pp->rv);
  }

  pp->v = p[9];

  return 0;
}