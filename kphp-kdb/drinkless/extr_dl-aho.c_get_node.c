#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ cnt; scalar_t__ code; scalar_t__ is_end; int /*<<< orphan*/ * h; struct TYPE_5__* v; } ;
typedef  TYPE_1__ trie_node ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* free_trie_nodes ; 
 scalar_t__ free_trie_nodes_cnt ; 
 TYPE_1__* malloc (int) ; 

trie_node *get_node (void) {
  if (free_trie_nodes_cnt == 0) {
    int add = 10000;
    free_trie_nodes = malloc (sizeof (trie_node) * add);
    assert (free_trie_nodes != NULL);
    free_trie_nodes_cnt += add;

    int i;
    for (i = 0; i + 1 < add; i++) {
      free_trie_nodes [i].v = &free_trie_nodes [i + 1];
    }
    free_trie_nodes [add - 1].v = NULL;
  }
  free_trie_nodes_cnt--;

  trie_node *res = free_trie_nodes;
  free_trie_nodes = free_trie_nodes->v;

  res->v = NULL;
  res->h = NULL;
  res->is_end = 0;
  res->code = 0;
  res->cnt = 0;

  return res;
}