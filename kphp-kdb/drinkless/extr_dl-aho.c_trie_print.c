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
struct TYPE_3__ {char code; struct TYPE_3__* h; struct TYPE_3__* v; scalar_t__ is_end; } ;
typedef  TYPE_1__ trie_node ;

/* Variables and functions */
 int /*<<< orphan*/  puts (char*) ; 

void trie_print (trie_node *v) {
  static char s[100000];
  static int sn = 0;
  while (v) {
    s[sn++] = v->code;
    if (v->is_end) {
      s[sn] = 0;
      puts (s);
    }
    trie_print (v->v);
    sn--;
    v = v->h;
  }
}