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
struct TYPE_3__ {int en; scalar_t__* edges; } ;
typedef  TYPE_1__ trie_arr_node ;
typedef  scalar_t__ CHAR ;

/* Variables and functions */

int trie_arr_getc (trie_arr_node *v, CHAR c) {
  int n = v->en;
  if (n > 5) {  // n MUST be > 0
    int l = 0, r = n;

    while (l + 1 < r) {
      int cc = (l + r) / 2;
      if (v->edges[cc * 2 + 1] <= c) {
        l = cc;
      } else {
        r = cc;
      }
    }

    return v->edges[l * 2 + 1] == c ? v->edges[l * 2] : 0;
  }

  int i;

  for (i = 0; i < n; i++) {
    if (v->edges[2 * i + 1] == c) {
      return v->edges[2 * i];
    }
  }
  return 0;
}