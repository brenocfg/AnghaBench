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
struct TYPE_4__ {scalar_t__ code; struct TYPE_4__* v; scalar_t__ is_end; int /*<<< orphan*/  cnt; struct TYPE_4__* h; } ;
typedef  TYPE_1__ trie_node ;
typedef  scalar_t__ CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  trie_check (TYPE_1__*,scalar_t__*) ; 

void trie_del (trie_node *v, CHAR *s) {
  if (!trie_check (v, s)) {
    return;
  }

  while (1) {
    while (v && v->code != *s) {
      v = v->h;
    }
    s++;
    v->cnt--;
    if (*s == 0) {
      v->is_end = 0;
      break;
    }

    v = v->v;
  }
}