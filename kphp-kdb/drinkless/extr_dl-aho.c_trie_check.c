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
struct TYPE_3__ {scalar_t__ code; int is_end; struct TYPE_3__* v; struct TYPE_3__* h; } ;
typedef  TYPE_1__ trie_node ;
typedef  scalar_t__ CHAR ;

/* Variables and functions */

int trie_check (trie_node *v, CHAR *s) {
  while (1) {
    while (v && v->code != *s) {
      v = v->h;
    }
    if (v == NULL) {
      return 0;
    }
    s++;
    if (*s == 0) {
      return v->is_end;
    }
    v = v->v;
  }
}