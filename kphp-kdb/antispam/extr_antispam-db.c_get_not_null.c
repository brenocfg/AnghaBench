#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ next; scalar_t__ ch; } ;
typedef  TYPE_1__ trie_node_t ;
typedef  int byte ;

/* Variables and functions */

__attribute__((used)) static trie_node_t **get_not_null (trie_node_t *v, byte i) {
  if (v->ch) {
    return (trie_node_t **)&v->next;
  } else {
    return ((trie_node_t **)v->next) + i;
  }
}