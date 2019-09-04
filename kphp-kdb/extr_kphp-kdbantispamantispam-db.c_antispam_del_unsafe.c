#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ patterns_cnt; scalar_t__ deg; scalar_t__ ch; struct TYPE_8__* next; int /*<<< orphan*/  p_ch; struct TYPE_8__* parent; } ;
typedef  TYPE_1__ trie_node_t ;
struct TYPE_9__ {TYPE_1__* trie_node; } ;
typedef  TYPE_2__ pattern_t ;
typedef  scalar_t__* list_pattern_link_t ;
typedef  int /*<<< orphan*/  hash_t ;
typedef  scalar_t__ byte ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_PATTERN (TYPE_2__) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__* get_not_null (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  id_to_pattern ; 
 int id_to_pattern_delete (int /*<<< orphan*/ ,int) ; 
 scalar_t__ list_pattern_delete (scalar_t__*,TYPE_2__*) ; 
 int /*<<< orphan*/  triple_to_pattern ; 
 int triple_to_patterns_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* triple_to_patterns_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (TYPE_1__*,int) ; 

__attribute__((used)) static inline void antispam_del_unsafe (int id, pattern_t* pattern) {
  trie_node_t *v = pattern->trie_node;
  --v->patterns_cnt;

  hash_t hash = HASH_PATTERN (*pattern);
  list_pattern_link_t head = triple_to_patterns_find (triple_to_pattern, hash);
  assert (head && list_pattern_delete (head, pattern));
  if (*head == 0) {
    assert (triple_to_patterns_delete (triple_to_pattern, hash));
  }
  assert (id_to_pattern_delete (id_to_pattern, id));

  while (v->parent != 0 && v->deg == 0 && v->patterns_cnt == 0) {
    trie_node_t *p = v->parent;
    *get_not_null (p, v->p_ch) = 0;
    if (--p->deg == 1) {
      trie_node_t *tmp, **e = (trie_node_t **)p->next;
      byte i = 0;
      while (!*e) {
        e++;
        i++;
      }
      tmp = *e;
      zfree (p->next, sizeof (trie_node_t *) * 256);
      p->next = tmp, p->ch = i;
    }
    zfree (v, sizeof (trie_node_t));
    v = p;
  }
}