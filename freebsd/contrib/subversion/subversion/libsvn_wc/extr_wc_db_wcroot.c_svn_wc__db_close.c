#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char const* abspath; scalar_t__ sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
struct TYPE_7__ {int /*<<< orphan*/ * state_pool; int /*<<< orphan*/ * dir_data; } ;
typedef  TYPE_2__ svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  svn_wc__db_close_many_wcroots (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_close(svn_wc__db_t *db)
{
  apr_pool_t *scratch_pool = db->state_pool;
  apr_hash_t *roots = apr_hash_make(scratch_pool);
  apr_hash_index_t *hi;

  /* Collect all the unique WCROOT structures, and empty out DIR_DATA.  */
  for (hi = apr_hash_first(scratch_pool, db->dir_data);
       hi;
       hi = apr_hash_next(hi))
    {
      svn_wc__db_wcroot_t *wcroot = apr_hash_this_val(hi);
      const char *local_abspath = apr_hash_this_key(hi);

      if (wcroot->sdb)
        svn_hash_sets(roots, wcroot->abspath, wcroot);

      svn_hash_sets(db->dir_data, local_abspath, NULL);
    }

  /* Run the cleanup for each WCROOT.  */
  return svn_error_trace(svn_wc__db_close_many_wcroots(roots, db->state_pool,
                                                       scratch_pool));
}