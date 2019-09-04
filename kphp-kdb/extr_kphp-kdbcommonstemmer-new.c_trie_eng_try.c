#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* ne; scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ MAX_TYPE ; 
 int best_d ; 
 scalar_t__ best_t ; 
 TYPE_1__* mem ; 

void trie_eng_try (int root, int *s, int n) {
  int v = root;
  best_t = MAX_TYPE;

  while (n--) {
    if (!mem[v].ne[s[n]]) {
      break;
    }
    v = mem[v].ne[s[n]];
    if (mem[v].type) {
      best_t = mem[v].type;
      best_d = n;
    }
  }
}