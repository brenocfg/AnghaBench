#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  word; } ;
typedef  TYPE_1__ query_node_t ;
typedef  int /*<<< orphan*/  hash_t ;

/* Variables and functions */
 TYPE_1__* new_query_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qn_word ; 

__attribute__((used)) static query_node_t *query_word_node (hash_t word) {
  /*  --- the following optimization is incorrect in general ---
      int i;
      for (i = 0; i < Q_nodes; i++) {
      if (QV[i].op == qn_word && QV[i].word == word) {
      return &QV[i];
      }
      }
   */
  query_node_t *X = new_query_node (qn_word);
  if (!X) {
    return 0;
  }
  X->word = word;
  return X;
}