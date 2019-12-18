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
typedef  int /*<<< orphan*/  node_t ;
typedef  int /*<<< orphan*/  authz_rule_segment_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * create_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static node_t *
ensure_node(node_t **node,
            authz_rule_segment_t *segment,
            apr_pool_t *result_pool)
{
  if (!*node)
    *node = create_node(segment, result_pool);

  return *node;
}