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
struct hash_word {int /*<<< orphan*/  sum; } ;
typedef  int /*<<< orphan*/  hash_t ;

/* Variables and functions */
 struct hash_word* get_hash_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_idx_word_list_len (int /*<<< orphan*/ ) ; 

int get_word_count_nomult (hash_t word) {
  struct hash_word *W = get_hash_node (word, 0);
  return get_idx_word_list_len (word) + (W ? W->sum : 0);
}