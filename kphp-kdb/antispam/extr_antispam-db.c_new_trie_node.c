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
struct TYPE_5__ {int ch; scalar_t__ deg; struct TYPE_5__* parent; int /*<<< orphan*/  p_ch; scalar_t__ patterns_cnt; scalar_t__ used; scalar_t__ next; } ;
typedef  TYPE_1__ trie_node_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 TYPE_1__* zmalloc (int) ; 

__attribute__((used)) static trie_node_t *new_trie_node (byte p_ch, trie_node_t *parent) {
  trie_node_t *p = zmalloc (sizeof (trie_node_t));
  if (parent != 0) {
    parent->deg++;
  }
  p->ch = 1;
  p->next = 0; // there are no edges
  p->used = 0;
  p->patterns_cnt = 0;
  p->p_ch = p_ch;
  p->parent = parent;
  p->deg = 0;
  return p;
}