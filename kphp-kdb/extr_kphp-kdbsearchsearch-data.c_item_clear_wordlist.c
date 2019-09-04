#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tree {int /*<<< orphan*/  word; struct tree* next; } ;
typedef  struct tree tree_t ;
typedef  int /*<<< orphan*/  item_t ;

/* Variables and functions */
 int /*<<< orphan*/  Root ; 
 int /*<<< orphan*/  tree_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void item_clear_wordlist (item_t *I, tree_t **p_I_words) {
  if (p_I_words == NULL) {
    return;
  }
  struct tree *p = *p_I_words;
  while (p) {
    tree_t *w = p->next;
    Root = tree_delete (Root, p->word, I);
    p = w;
  }
  *p_I_words = NULL;
}