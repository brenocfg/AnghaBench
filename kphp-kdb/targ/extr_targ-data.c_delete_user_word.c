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
struct hash_word {int /*<<< orphan*/  sum; int /*<<< orphan*/  num; int /*<<< orphan*/  word_tree; } ;
typedef  int /*<<< orphan*/  hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  WordSpace ; 
 struct hash_word* get_hash_node (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intree_incr_z (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

void delete_user_word (int uid, hash_t word) {
  struct hash_word *W = get_hash_node (word, 1);
  //!!! ASSERT there is enough occurences of such word in index (needs additional feedback from intree_incr_z?)
  W->word_tree = intree_incr_z (WordSpace, W->word_tree, uid, -1, &W->num);
  --W->sum;
}