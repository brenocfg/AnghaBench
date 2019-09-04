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
struct TYPE_5__ {int en; char* edges; scalar_t__ is_end; } ;
typedef  TYPE_1__ trie_arr_node ;

/* Variables and functions */
 TYPE_1__* TSHIFT (TYPE_1__*,char) ; 

void trie_arr_text_save (trie_arr_node *v, char *buff, int *bn) {
  static char s[100000];
  static int sn = 0;
  int i;
  if (v->is_end) {
    s[sn] = 0;
    //puts (s);
    for (i = 0; i < sn; i++) {
      buff[(*bn)++] = s[i];
    }
    buff[(*bn)++] = '\t';
  }

  for (i = 0; i < v->en; i++) {
    s[sn++] = v->edges[i * 2 + 1];

    trie_arr_text_save (TSHIFT(v, v->edges[2 * i]), buff, bn);
    sn--;
  }
}