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
struct TYPE_3__ {size_t op; int /*<<< orphan*/  word; } ;
typedef  TYPE_1__ query_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  kprintf (char*,char const*,char*,int /*<<< orphan*/ ) ; 

void dump_op_type (const char *msg, query_node_t *X) {
  static char *ops[] = {"qn_false", "qn_true", "qn_word", "qn_and", "qn_or", "qn_minus", "qn_error", "qn_cum_and", "qn_cum_or"};
  kprintf ("%s: %s %llx\n", msg, ops[X->op], X->word);
}