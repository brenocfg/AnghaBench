#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* path; int /*<<< orphan*/  db; int /*<<< orphan*/  abspath; scalar_t__ closed; } ;
typedef  TYPE_1__ svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 scalar_t__ IS_MISSING (TYPE_1__*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_single (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* get_from_shared (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  svn_dirent_is_ancestor (char*,char const*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_temp_clear_access (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__db_temp_get_all_access (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
do_close(svn_wc_adm_access_t *adm_access,
         svn_boolean_t preserve_lock,
         apr_pool_t *scratch_pool)
{
  svn_wc_adm_access_t *look;

  if (adm_access->closed)
    return SVN_NO_ERROR;

  /* If we are part of the shared set, then close descendant batons.  */
  look = get_from_shared(adm_access->abspath, adm_access->db, scratch_pool);
  if (look != NULL)
    {
      apr_hash_t *opened;
      apr_hash_index_t *hi;

      /* Gather all the opened access batons from the DB.  */
      opened = svn_wc__db_temp_get_all_access(adm_access->db, scratch_pool);

      /* Close any that are descendants of this baton.  */
      for (hi = apr_hash_first(scratch_pool, opened);
           hi;
           hi = apr_hash_next(hi))
        {
          const char *abspath = apr_hash_this_key(hi);
          svn_wc_adm_access_t *child = apr_hash_this_val(hi);
          const char *path = child->path;

          if (IS_MISSING(child))
            {
              /* We don't close the missing entry, but get rid of it from
                 the set. */
              svn_wc__db_temp_clear_access(adm_access->db, abspath,
                                           scratch_pool);
              continue;
            }

          if (! svn_dirent_is_ancestor(adm_access->path, path)
              || strcmp(adm_access->path, path) == 0)
            continue;

          SVN_ERR(close_single(child, preserve_lock, scratch_pool));
        }
    }

  return svn_error_trace(close_single(adm_access, preserve_lock,
                                      scratch_pool));
}