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
struct TYPE_7__ {TYPE_2__* root; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_3__ svn_prefix_tree__t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {float* data; } ;
struct TYPE_6__ {TYPE_1__ key; } ;

/* Variables and functions */
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 

svn_prefix_tree__t *
svn_prefix_tree__create(apr_pool_t *pool)
{
  svn_prefix_tree__t *tree = apr_pcalloc(pool, sizeof(*tree));
  tree->pool = pool;

  tree->root = apr_pcalloc(pool, sizeof(*tree->root));
  tree->root->key.data[7] = '\xff'; /* This is not a leaf. See is_leaf(). */

  return tree;
}