#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int suff; int en; int* edges; int /*<<< orphan*/  is_end; } ;
typedef  TYPE_1__ trie_arr_node ;

/* Variables and functions */
 TYPE_1__* TSHIFT (TYPE_1__*,int) ; 
 int maxq ; 
 int trie_arr_getc (TYPE_1__*,int) ; 

void trie_arr_aho (trie_arr_node *st) {
#define maxq 100000
  size_t q[maxq];
  int l = 0, r = 0;

  st->suff = 0;
  q[r++] = 0;

  while (l < r) {
    int dv = q[l++];
    //fprintf (stderr, "dv = %d\n", dv);
    trie_arr_node *v = TSHIFT (st, dv);

    int i;
    for (i = 0; i < v->en; i++) {
      int c = v->edges[2 * i + 1];
      trie_arr_node *nv = TSHIFT (v, v->edges[2 * i]), *p = v;
      q[r++] = v->edges[2 * i] + dv;
      int add = 0;
      do {
        add += p->suff;
        p = TSHIFT (p, p->suff);
      } while (p->suff && !trie_arr_getc (p, c));
      int x = 0;
      if (p != v) {
	      x = trie_arr_getc (p, c);
      }
      nv->suff = -v->edges[2 * i] + add + x;
      nv->is_end |= TSHIFT(nv, nv->suff)->is_end;
    }
  }
#undef maxq
}