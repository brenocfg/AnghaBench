#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_10__ {TYPE_4__* priv; } ;
typedef  TYPE_3__ svn_ra_session_t ;
struct TYPE_11__ {int /*<<< orphan*/  callback_baton; TYPE_2__* callbacks; TYPE_1__* fs_path; int /*<<< orphan*/  fs; } ;
typedef  TYPE_4__ svn_ra_local__session_baton_t ;
typedef  int /*<<< orphan*/  svn_ra_dirent_receiver_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int svn_boolean_t ;
struct TYPE_12__ {void* receiver_baton; int /*<<< orphan*/  receiver; } ;
typedef  TYPE_5__ dirent_receiver_baton_t ;
typedef  int apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_9__ {int /*<<< orphan*/ * cancel_func; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int SVN_DIRENT_KIND ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dirent_receiver ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_list (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
svn_ra_local__list(svn_ra_session_t *session,
                   const char *path,
                   svn_revnum_t revision,
                   const apr_array_header_t *patterns,
                   svn_depth_t depth,
                   apr_uint32_t dirent_fields,
                   svn_ra_dirent_receiver_t receiver,
                   void *receiver_baton,
                   apr_pool_t *pool)
{
  svn_ra_local__session_baton_t *sess = session->priv;
  svn_fs_root_t *root;
  svn_boolean_t path_info_only = (dirent_fields & ~SVN_DIRENT_KIND) == 0;

  dirent_receiver_baton_t baton;
  baton.receiver = receiver;
  baton.receiver_baton = receiver_baton;

  SVN_ERR(svn_fs_revision_root(&root, sess->fs, revision, pool));
  path = svn_dirent_join(sess->fs_path->data, path, pool);
  return svn_error_trace(svn_repos_list(root, path, patterns, depth,
                                        path_info_only, NULL, NULL,
                                        dirent_receiver, &baton,
                                        sess->callbacks
                                          ? sess->callbacks->cancel_func
                                          : NULL,
                                        sess->callback_baton, pool));
}