#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t change_kind; int /*<<< orphan*/  prop_mod; int /*<<< orphan*/  text_mod; int /*<<< orphan*/  node_kind; int /*<<< orphan*/  copyfrom_rev; int /*<<< orphan*/  copyfrom_path; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ svn_repos_path_change_t ;
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {scalar_t__ started; int /*<<< orphan*/ * conn; } ;
typedef  TYPE_2__ log_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 size_t svn_fs_path_change_modify ; 
 size_t svn_fs_path_change_replace ; 
 int /*<<< orphan*/  svn_ra_svn__start_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__write_data_log_changed_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
path_change_receiver(void *baton,
                     svn_repos_path_change_t *change,
                     apr_pool_t *scratch_pool)
{
  const char symbol[] = "MADR";

  log_baton_t *b = baton;
  svn_ra_svn_conn_t *conn = b->conn;

  /* Sanitize and convert change kind to ra-svn level action.

     Pushing that conversion down into libsvn_ra_svn would add yet another
     API dependency there. */
  char action = (   change->change_kind < svn_fs_path_change_modify
                 || change->change_kind > svn_fs_path_change_replace)
              ? 0
              : symbol[change->change_kind];

  /* Open lists once: LOG_ENTRY and LOG_ENTRY->CHANGED_PATHS. */
  if (!b->started)
    {
      SVN_ERR(svn_ra_svn__start_list(conn, scratch_pool));
      SVN_ERR(svn_ra_svn__start_list(conn, scratch_pool));
      b->started = TRUE;
    }

  /* Serialize CHANGE. */
  SVN_ERR(svn_ra_svn__write_data_log_changed_path(
              conn, scratch_pool,
              &change->path,
              action,
              change->copyfrom_path,
              change->copyfrom_rev,
              change->node_kind,
              change->text_mod,
              change->prop_mod));

  return SVN_NO_ERROR;
}