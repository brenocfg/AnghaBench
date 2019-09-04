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
struct TYPE_3__ {int op; struct TYPE_3__* right; struct TYPE_3__* left; int /*<<< orphan*/  word; } ;
typedef  TYPE_1__ query_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_word_frequency (int /*<<< orphan*/ ) ; 
#define  qn_and 133 
#define  qn_false 132 
#define  qn_minus 131 
#define  qn_or 130 
#define  qn_true 129 
#define  qn_word 128 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void dump_query_tree (query_node_t *X) {
  if (!X) {
    fprintf (stderr, "(NULL)");
    return;
  }
  switch (X->op) {
    case qn_false:
      fprintf (stderr, "(false)");
      return;
    case qn_true:
      fprintf (stderr, "(true)");
      return;
    case qn_word:
      fprintf (stderr, "(word %016llx, freq = %d)", X->word, get_word_frequency (X->word));
      return;
    case qn_and:
      fprintf (stderr, "(and ");
      break;
    case qn_or:
      fprintf (stderr, "(or ");
      break;
    case qn_minus:
      fprintf (stderr, "(minus ");
      break;
    default:
      fprintf (stderr, "(???%d ", X->op);
  }
  dump_query_tree (X->left);
  fprintf (stderr, " ");
  dump_query_tree (X->right);
  fprintf (stderr, ")");
}