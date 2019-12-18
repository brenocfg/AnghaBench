#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* svn_repos_dirent_receiver_t ) (char const*,TYPE_1__*,void*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  kind; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ svn_dirent_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  fill_dirent (TYPE_1__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
report_dirent(svn_fs_root_t *root,
              const char *path,
              svn_node_kind_t kind,
              svn_boolean_t path_info_only,
              svn_repos_dirent_receiver_t receiver,
              void *receiver_baton,
              apr_pool_t *scratch_pool)
{
  svn_dirent_t dirent = { 0 };

  /* Fetch the details to report - if required. */
  dirent.kind = kind;
  if (!path_info_only)
    SVN_ERR(fill_dirent(&dirent, root, path, scratch_pool));

  /* Report the entry. */
  SVN_ERR(receiver(path, &dirent, receiver_baton, scratch_pool));

  return SVN_NO_ERROR;
}