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
struct condition_with_hash {void* word2; void* word; void* false_branch; void* true_branch; int /*<<< orphan*/  eval; } ;
typedef  void* hash_t ;
typedef  void* condition_t ;
typedef  int /*<<< orphan*/  condition_func_t ;

/* Variables and functions */
 struct condition_with_hash* zmalloc (int) ; 

__attribute__((used)) static condition_t compile_condition_twowords (hash_t word, hash_t word2, condition_t true_branch, condition_t false_branch, condition_func_t check_word) {
  struct condition_with_hash *A = zmalloc (sizeof (struct condition_with_hash));
  A->eval = check_word;
  A->true_branch = true_branch;
  A->false_branch = false_branch;
  A->word = word;
  A->word2 = word2;
  return (condition_t) A;
}