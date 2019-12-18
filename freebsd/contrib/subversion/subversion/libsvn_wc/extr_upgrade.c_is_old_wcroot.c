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
struct TYPE_3__ {scalar_t__ schedule; scalar_t__ depth; scalar_t__ deleted; scalar_t__ absent; } ;
typedef  TYPE_1__ svn_wc_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_WC_INVALID_OP_ON_CWD ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ svn_depth_exclude ; 
 scalar_t__ svn_dirent_is_root (char const*,int /*<<< orphan*/ ) ; 
 char* svn_dirent_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_split (char const**,char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * svn_wc__read_entries_old (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_schedule_add ; 

__attribute__((used)) static svn_error_t *
is_old_wcroot(const char *local_abspath,
              apr_pool_t *scratch_pool)
{
  apr_hash_t *entries;
  const char *parent_abspath, *name;
  svn_wc_entry_t *entry;
  svn_error_t *err = svn_wc__read_entries_old(&entries, local_abspath,
                                              scratch_pool, scratch_pool);
  if (err)
    {
      return svn_error_createf(
        SVN_ERR_WC_INVALID_OP_ON_CWD, err,
        _("Can't upgrade '%s' as it is not a working copy"),
        svn_dirent_local_style(local_abspath, scratch_pool));
    }
  else if (svn_dirent_is_root(local_abspath, strlen(local_abspath)))
    return SVN_NO_ERROR;

  svn_dirent_split(&parent_abspath, &name, local_abspath, scratch_pool);

  err = svn_wc__read_entries_old(&entries, parent_abspath,
                                 scratch_pool, scratch_pool);
  if (err)
    {
      svn_error_clear(err);
      return SVN_NO_ERROR;
    }

  entry = svn_hash_gets(entries, name);
  if (!entry
      || entry->absent
      || (entry->deleted && entry->schedule != svn_wc_schedule_add)
      || entry->depth == svn_depth_exclude)
    {
      return SVN_NO_ERROR;
    }

  while (!svn_dirent_is_root(parent_abspath, strlen(parent_abspath)))
    {
      svn_dirent_split(&parent_abspath, &name, parent_abspath, scratch_pool);
      err = svn_wc__read_entries_old(&entries, parent_abspath,
                                     scratch_pool, scratch_pool);
      if (err)
        {
          svn_error_clear(err);
          parent_abspath = svn_dirent_join(parent_abspath, name, scratch_pool);
          break;
        }
      entry = svn_hash_gets(entries, name);
      if (!entry
          || entry->absent
          || (entry->deleted && entry->schedule != svn_wc_schedule_add)
          || entry->depth == svn_depth_exclude)
        {
          parent_abspath = svn_dirent_join(parent_abspath, name, scratch_pool);
          break;
        }
    }

  return svn_error_createf(
    SVN_ERR_WC_INVALID_OP_ON_CWD, NULL,
    _("Can't upgrade '%s' as it is not a working copy root,"
      " the root is '%s'"),
    svn_dirent_local_style(local_abspath, scratch_pool),
    svn_dirent_local_style(parent_abspath, scratch_pool));
}