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
typedef  int /*<<< orphan*/  svn_branch__rev_bid_t ;
struct TYPE_4__ {int /*<<< orphan*/  parents; } ;
typedef  TYPE_1__ svn_branch__history_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_this_val (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_branch__rev_bid_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

svn_branch__history_t *
svn_branch__history_create(apr_hash_t *parents,
                           apr_pool_t *result_pool)
{
  svn_branch__history_t *history
    = apr_pcalloc(result_pool, sizeof(*history));

  history->parents = apr_hash_make(result_pool);
  if (parents)
    {
      apr_hash_index_t *hi;

      for (hi = apr_hash_first(result_pool, parents);
           hi; hi = apr_hash_next(hi))
        {
          const char *bid = apr_hash_this_key(hi);
          svn_branch__rev_bid_t *val = apr_hash_this_val(hi);

          svn_hash_sets(history->parents,
                        apr_pstrdup(result_pool, bid),
                        svn_branch__rev_bid_dup(val, result_pool));
        }
    }
  return history;
}