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
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svn_wc__db_base_get_dav_cache (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_base_set_dav_cache (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
wcprop_set(svn_wc__db_t *db,
           const char *local_abspath,
           const char *name,
           const svn_string_t *value,
           apr_pool_t *scratch_pool)
{
  apr_hash_t *prophash;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));

  /* Note: this is not well-transacted. But... meh. This is merely a cache,
     and if two processes are trying to modify this one entry at the same
     time, then fine: we can let one be a winner, and one a loser. Of course,
     if there are *other* state changes afoot, then the lack of a txn could
     be a real issue, but we cannot solve that here.  */

  SVN_ERR(svn_wc__db_base_get_dav_cache(&prophash, db, local_abspath,
                                        scratch_pool, scratch_pool));

  if (prophash == NULL)
    prophash = apr_hash_make(scratch_pool);

  svn_hash_sets(prophash, name, value);
  return svn_error_trace(svn_wc__db_base_set_dav_cache(db, local_abspath,
                                                       prophash,
                                                       scratch_pool));
}