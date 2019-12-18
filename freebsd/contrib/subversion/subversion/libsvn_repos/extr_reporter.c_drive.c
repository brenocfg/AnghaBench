#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
struct TYPE_16__ {scalar_t__ kind; } ;
typedef  TYPE_2__ svn_fs_dirent_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
struct TYPE_17__ {char* t_path; TYPE_1__* editor; int /*<<< orphan*/  requested_depth; scalar_t__* s_operand; int /*<<< orphan*/  edit_baton; int /*<<< orphan*/  t_rev; int /*<<< orphan*/ * t_root; int /*<<< orphan*/  fs_base; } ;
typedef  TYPE_3__ report_baton_t ;
struct TYPE_18__ {int /*<<< orphan*/  depth; int /*<<< orphan*/  start_empty; int /*<<< orphan*/  link_path; int /*<<< orphan*/  rev; } ;
typedef  TYPE_4__ path_info_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_15__ {int /*<<< orphan*/  (* close_directory ) (void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* open_root ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ;int /*<<< orphan*/  (* set_target_revision ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_AUTHZ_ROOT_UNREADABLE ; 
 int /*<<< orphan*/  SVN_ERR_FS_PATH_SYNTAX ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  check_auth (TYPE_3__*,int*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delta_dirs (TYPE_3__*,int /*<<< orphan*/ ,char const*,char const*,void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fake_dirent (TYPE_2__ const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_source_root (TYPE_3__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  stub3 (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 char* svn_fspath__dirname (char*,int /*<<< orphan*/ *) ; 
 char* svn_fspath__join (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/  update_entry (TYPE_3__*,int /*<<< orphan*/ ,char const*,TYPE_2__ const*,char const*,TYPE_2__ const*,void*,scalar_t__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
drive(report_baton_t *b, svn_revnum_t s_rev, path_info_t *info,
      apr_pool_t *pool)
{
  const char *t_anchor, *s_fullpath;
  svn_boolean_t allowed, info_is_set_path;
  svn_fs_root_t *s_root;
  const svn_fs_dirent_t *s_entry, *t_entry;
  void *root_baton;

  /* Compute the target path corresponding to the working copy anchor,
     and check its authorization. */
  t_anchor = *b->s_operand ? svn_fspath__dirname(b->t_path, pool) : b->t_path;
  SVN_ERR(check_auth(b, &allowed, t_anchor, pool));
  if (!allowed)
    return svn_error_create
      (SVN_ERR_AUTHZ_ROOT_UNREADABLE, NULL,
       _("Not authorized to open root of edit operation"));

  /* Collect information about the source and target nodes. */
  s_fullpath = svn_fspath__join(b->fs_base, b->s_operand, pool);
  SVN_ERR(get_source_root(b, &s_root, s_rev));
  SVN_ERR(fake_dirent(&s_entry, s_root, s_fullpath, pool));
  SVN_ERR(fake_dirent(&t_entry, b->t_root, b->t_path, pool));

  /* If the operand is a locally added file or directory, it won't
     exist in the source, so accept that. */
  info_is_set_path = (SVN_IS_VALID_REVNUM(info->rev) && !info->link_path);
  if (info_is_set_path && !s_entry)
    s_fullpath = NULL;

  /* Check if the target path exists first.  */
  if (!*b->s_operand && !(t_entry))
    return svn_error_createf(SVN_ERR_FS_PATH_SYNTAX, NULL,
                             _("Target path '%s' does not exist"),
                             b->t_path);

  /* If the anchor is the operand, the source and target must be dirs.
     Check this before opening the root to avoid modifying the wc. */
  else if (!*b->s_operand && (!s_entry || s_entry->kind != svn_node_dir
                              || t_entry->kind != svn_node_dir))
    return svn_error_create(SVN_ERR_FS_PATH_SYNTAX, NULL,
                            _("Cannot replace a directory from within"));

  SVN_ERR(b->editor->set_target_revision(b->edit_baton, b->t_rev, pool));
  SVN_ERR(b->editor->open_root(b->edit_baton, s_rev, pool, &root_baton));

  /* If the anchor is the operand, diff the two directories; otherwise
     update the operand within the anchor directory. */
  if (!*b->s_operand)
    SVN_ERR(delta_dirs(b, s_rev, s_fullpath, b->t_path, root_baton,
                       "", info->start_empty, info->depth, b->requested_depth,
                       pool));
  else
    SVN_ERR(update_entry(b, s_rev, s_fullpath, s_entry, b->t_path,
                         t_entry, root_baton, b->s_operand, info,
                         info->depth, b->requested_depth, pool));

  return svn_error_trace(b->editor->close_directory(root_baton, pool));
}