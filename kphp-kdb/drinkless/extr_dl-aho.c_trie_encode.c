#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int code; int is_end; struct TYPE_4__* h; struct TYPE_4__* v; scalar_t__ cnt; } ;
typedef  TYPE_1__ trie_node ;
struct TYPE_5__ {int* edges; int en; int is_end; } ;
typedef  TYPE_2__ trie_arr_node ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cmp_tx ; 
 int /*<<< orphan*/  qsort (int*,int,int,int /*<<< orphan*/ ) ; 

size_t trie_encode (trie_node *v, char *buff, int is_end) {
  char *st = buff;

  size_t vsize = sizeof (int) * 3;

  int en = 0;
  trie_node *tv = v;

  trie_arr_node *nv = (trie_arr_node *)st;
  assert (vsize == (char *)&nv->edges - (char *)nv);

  while (tv != NULL) {
    en += !!tv->cnt;
    tv = tv->h;
  }

  vsize += sizeof (int) * 2 * en;
  buff += vsize;

  tv = v;
  int in = 0;
  while (tv != NULL) {
    if (tv->cnt) {
      nv->edges[in * 2 + 1] = tv->code;
      nv->edges[in * 2] = buff - st;
      buff += trie_encode (tv->v, buff, tv->is_end);
      in++;
    }

    tv = tv->h;
  }

  qsort (nv->edges, en, sizeof (int) * 2, cmp_tx);

  nv->en = en;
  nv->is_end = is_end;

  return buff - st;
}