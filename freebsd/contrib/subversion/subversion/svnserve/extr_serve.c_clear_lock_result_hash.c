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
struct lock_result_t {int /*<<< orphan*/  err; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 struct lock_result_t* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
clear_lock_result_hash(apr_hash_t *results,
                       apr_pool_t *scratch_pool)
{
  apr_hash_index_t *hi;

  for (hi = apr_hash_first(scratch_pool, results); hi; hi = apr_hash_next(hi))
    {
      struct lock_result_t *result = apr_hash_this_val(hi);
      svn_error_clear(result->err);
    }
}