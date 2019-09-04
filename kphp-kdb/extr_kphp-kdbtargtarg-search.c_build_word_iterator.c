#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ treeref_t ;
struct TYPE_4__ {scalar_t__ mult; scalar_t__ pos; } ;
struct TYPE_3__ {scalar_t__ mult; scalar_t__ pos; } ;
struct wordlist_tree_iterator {scalar_t__ mult; scalar_t__ pos; TYPE_2__ TS; TYPE_1__ WS; int /*<<< orphan*/  (* jump_to ) (int /*<<< orphan*/ ,scalar_t__) ;} ;
struct wordlist_iterator {scalar_t__ mult; scalar_t__ pos; int /*<<< orphan*/  jump_to; TYPE_1__ WS; } ;
struct tree_iterator {scalar_t__ mult; scalar_t__ pos; int /*<<< orphan*/  jump_to; TYPE_2__ TS; } ;
struct hash_word {scalar_t__ word_tree; } ;
typedef  int /*<<< orphan*/  iterator_t ;
typedef  int /*<<< orphan*/  hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  build_empty_iterator () ; 
 struct hash_word* get_hash_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char* idx_word_lookup (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  init_tree_subiterator (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  init_wordlist_subiterator (TYPE_1__*,unsigned char*,int) ; 
 int /*<<< orphan*/  tree_iterator_jump_to ; 
 int /*<<< orphan*/  wordlist_iterator_jump_to ; 
 int /*<<< orphan*/  wordlist_tree_iterator_jump_to (int /*<<< orphan*/ ,scalar_t__) ; 
 void* zmalloc (int) ; 

iterator_t build_word_iterator (hash_t word) {
  struct hash_word *W = get_hash_node (word, 0);
  treeref_t tree = W ? W->word_tree : 0;
  int len;
  unsigned char *data = idx_word_lookup (word, &len);
  assert (tree || data);
  if (!tree && !data) {
    return build_empty_iterator ();
  }
  if (!data) {
    struct tree_iterator *I = zmalloc (sizeof (struct tree_iterator));
    init_tree_subiterator (&I->TS, tree);
    assert ((I->mult = I->TS.mult) > 0);
    I->pos = I->TS.pos;
    I->jump_to = tree_iterator_jump_to;
    return (iterator_t) I;
  }
  if (!tree) {
    struct wordlist_iterator *I = zmalloc (sizeof (struct wordlist_iterator));
    init_wordlist_subiterator (&I->WS, data, len);
    assert ((I->mult = I->WS.mult) > 0);
    I->pos = I->WS.pos;
    I->jump_to = wordlist_iterator_jump_to;
    return (iterator_t) I;
  }
  struct wordlist_tree_iterator *I = zmalloc (sizeof (struct wordlist_tree_iterator));
  init_wordlist_subiterator (&I->WS, data, len);
  init_tree_subiterator (&I->TS, tree);
  I->jump_to = wordlist_tree_iterator_jump_to;
  if (I->TS.pos < I->WS.pos) {
    assert ((I->mult = I->TS.mult) > 0);
    I->pos = I->TS.pos;
  } else if (I->TS.pos > I->WS.pos) {
    assert ((I->mult = I->WS.mult) > 0);
    I->pos = I->WS.pos;
  } else if (I->TS.mult + I->WS.mult > 0) {
    I->mult = I->TS.mult + I->WS.mult;
    I->pos = I->TS.pos;
  } else {
    assert (I->TS.mult + I->WS.mult == 0);
    wordlist_tree_iterator_jump_to ((iterator_t) I, I->TS.pos + 1);
  }
  return (iterator_t) I;
}