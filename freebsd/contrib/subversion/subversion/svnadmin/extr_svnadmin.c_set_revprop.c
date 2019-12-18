#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ svn_stringbuf_t ;
struct TYPE_14__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_4__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_repos_t ;
typedef  int /*<<< orphan*/  svn_fs_txn_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {int /*<<< orphan*/  number; } ;
struct TYPE_12__ {TYPE_1__ value; } ;
struct svnadmin_opt_state {int /*<<< orphan*/  use_post_revprop_change_hook; int /*<<< orphan*/  use_pre_revprop_change_hook; TYPE_2__ start_revision; scalar_t__ txn_id; int /*<<< orphan*/  repository_path; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  open_repos (int /*<<< orphan*/ **,int /*<<< orphan*/ ,struct svnadmin_opt_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_change_txn_prop (int /*<<< orphan*/ *,char const*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_open_txn (int /*<<< orphan*/ **,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_repos_fs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_fs_change_rev_prop4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_string_create_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_from_file2 (TYPE_3__**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_translate_string2 (TYPE_4__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
set_revprop(const char *prop_name, const char *filename,
            struct svnadmin_opt_state *opt_state, apr_pool_t *pool)
{
  svn_repos_t *repos;
  svn_string_t *prop_value;

  if (filename)
    {
      svn_stringbuf_t *file_contents;

      SVN_ERR(svn_stringbuf_from_file2(&file_contents, filename, pool));

      prop_value = svn_string_create_empty(pool);
      prop_value->data = file_contents->data;
      prop_value->len = file_contents->len;

      SVN_ERR(svn_subst_translate_string2(&prop_value, NULL, NULL, prop_value,
                                          NULL, FALSE, pool, pool));
    }
  else
    {
      prop_value = NULL;
    }

  /* Open the filesystem  */
  SVN_ERR(open_repos(&repos, opt_state->repository_path, opt_state, pool));

  if (opt_state->txn_id)
    {
      svn_fs_t *fs = svn_repos_fs(repos);
      svn_fs_txn_t *txn;

      SVN_ERR(svn_fs_open_txn(&txn, fs, opt_state->txn_id, pool));
      SVN_ERR(svn_fs_change_txn_prop(txn, prop_name, prop_value, pool));
    }
  else
    SVN_ERR(svn_repos_fs_change_rev_prop4(
              repos, opt_state->start_revision.value.number,
              NULL, prop_name, NULL, prop_value,
              opt_state->use_pre_revprop_change_hook,
              opt_state->use_post_revprop_change_hook,
              NULL, NULL, pool));

  return SVN_NO_ERROR;
}