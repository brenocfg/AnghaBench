#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* priv; } ;
typedef  TYPE_3__ svn_branch__state_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {TYPE_1__* element_tree; } ;
struct TYPE_5__ {int /*<<< orphan*/  e_map; } ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_pool_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static apr_pool_t *
branch_state_pool_get(svn_branch__state_t *branch)
{
  return apr_hash_pool_get(branch->priv->element_tree->e_map);
}