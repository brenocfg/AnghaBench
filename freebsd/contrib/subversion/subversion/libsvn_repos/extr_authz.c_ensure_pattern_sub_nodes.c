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
struct TYPE_3__ {int /*<<< orphan*/ * pattern_sub_nodes; } ;
typedef  TYPE_1__ node_t ;
typedef  int /*<<< orphan*/  node_pattern_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_pcalloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static node_pattern_t *
ensure_pattern_sub_nodes(node_t *node,
                         apr_pool_t *result_pool)
{
  if (node->pattern_sub_nodes == NULL)
    node->pattern_sub_nodes = apr_pcalloc(result_pool,
                                          sizeof(*node->pattern_sub_nodes));

  return node->pattern_sub_nodes;
}