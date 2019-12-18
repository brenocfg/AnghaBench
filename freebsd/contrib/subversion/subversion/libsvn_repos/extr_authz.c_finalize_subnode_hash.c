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
typedef  int /*<<< orphan*/  limited_rights_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finalize_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
finalize_subnode_hash(apr_hash_t *hash,
                      limited_rights_t *sum,
                      apr_pool_t *scratch_pool)
{
  if (hash)
    {
      apr_hash_index_t *hi;
      for (hi = apr_hash_first(scratch_pool, hash);
           hi;
           hi = apr_hash_next(hi))
        finalize_tree(apr_hash_this_val(hi), sum, scratch_pool);
    }
}