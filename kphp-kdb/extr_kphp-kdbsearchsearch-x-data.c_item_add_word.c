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
struct TYPE_3__ {struct item* item; } ;
typedef  TYPE_1__ tree_t ;
struct item {int dummy; } ;
typedef  int /*<<< orphan*/  hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  Root ; 
 int /*<<< orphan*/  assert (int) ; 
 int lrand48 () ; 
 int /*<<< orphan*/  tree_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct item*,int,unsigned int) ; 
 TYPE_1__* tree_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct item*) ; 

__attribute__((used)) static void item_add_word (struct item *I, hash_t word, unsigned freqs) {
  tree_t *T = tree_lookup (Root, word, I);
  if (!T) {
    int y = lrand48 ();
    Root = tree_insert (Root, word, I, y, freqs);
  } else  {
    assert (T->item == I);
  }
}