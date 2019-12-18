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
struct TYPE_5__ {scalar_t__ code; int is_end; struct TYPE_5__* v; int /*<<< orphan*/  cnt; struct TYPE_5__* h; } ;
typedef  TYPE_1__ trie_node ;
typedef  scalar_t__ CHAR ;

/* Variables and functions */
 TYPE_1__* get_node () ; 
 scalar_t__ trie_check (TYPE_1__*,scalar_t__*) ; 

void trie_add (trie_node **v, CHAR *s) {
  if (trie_check (*v, s)) {
    return;
  }

  while (1) {
    //fprintf (stderr, "add <%s>\n", s);
    while (*v && (*v)->code != *s) {
      v = &(*v)->h;
    }
    if (*v == NULL) {
      *v = get_node();
      (*v)->code = *s;
    }
    s++;
    (*v)->cnt++;
    if (*s == 0) {
      (*v)->is_end = 1;
      break;
    }
    v = &(*v)->v;
  }
}