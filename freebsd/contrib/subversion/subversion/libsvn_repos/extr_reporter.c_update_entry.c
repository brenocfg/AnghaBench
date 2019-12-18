#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_22__ {int /*<<< orphan*/  token; } ;
typedef  TYPE_3__ svn_lock_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
struct TYPE_23__ {scalar_t__ kind; int /*<<< orphan*/  id; } ;
typedef  TYPE_4__ svn_fs_dirent_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_depth_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int svn_boolean_t ;
struct TYPE_24__ {TYPE_2__* editor; int /*<<< orphan*/ * t_root; scalar_t__ t_rev; scalar_t__ ignore_ancestry; TYPE_1__* repos; int /*<<< orphan*/  is_switch; } ;
typedef  TYPE_5__ report_baton_t ;
struct TYPE_25__ {char* link_path; int start_empty; int /*<<< orphan*/ * lock_token; scalar_t__ rev; } ;
typedef  TYPE_6__ path_info_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_21__ {int /*<<< orphan*/  (* close_file ) (void*,char const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* open_file ) (char const*,void*,scalar_t__,int /*<<< orphan*/ *,void**) ;int /*<<< orphan*/  (* close_directory ) (void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* add_directory ) (char const*,void*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,void**) ;int /*<<< orphan*/  (* open_directory ) (char const*,void*,scalar_t__,int /*<<< orphan*/ *,void**) ;int /*<<< orphan*/  (* absent_file ) (char const*,void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* absent_directory ) (char const*,void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* delete_entry ) (char const*,scalar_t__,void*,int /*<<< orphan*/ *) ;} ;
struct TYPE_20__ {int /*<<< orphan*/  fs; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_FOUND ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_file_smartly (TYPE_5__*,char const*,void*,char const*,void**,char const**,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  any_path_info (TYPE_5__*,char const*) ; 
 int /*<<< orphan*/  check_auth (TYPE_5__*,int*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delta_dirs (TYPE_5__*,scalar_t__,char const*,char const*,void*,char const*,int,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delta_files (TYPE_5__*,void*,scalar_t__,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fake_dirent (TYPE_4__ const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_source_root (TYPE_5__*,int /*<<< orphan*/ **,scalar_t__) ; 
 int /*<<< orphan*/  skip_path_info (TYPE_5__*,char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (char const*,scalar_t__,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (char const*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (char const*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (char const*,void*,scalar_t__,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  stub5 (char const*,void*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  stub6 (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub7 (char const*,void*,scalar_t__,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  stub8 (void*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 char* svn_checksum_to_cstring (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_check_path (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int svn_fs_compare_ids (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_contents_changed (int*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_file_checksum (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_get_lock (TYPE_3__**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_props_changed (int*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_root_fs (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  svn_repos_deleted_rev (int /*<<< orphan*/ ,char const*,scalar_t__,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
update_entry(report_baton_t *b, svn_revnum_t s_rev, const char *s_path,
             const svn_fs_dirent_t *s_entry, const char *t_path,
             const svn_fs_dirent_t *t_entry, void *dir_baton,
             const char *e_path, path_info_t *info, svn_depth_t wc_depth,
             svn_depth_t requested_depth, apr_pool_t *pool)
{
  svn_fs_root_t *s_root = NULL;
  svn_boolean_t allowed, related;
  void *new_baton;
  svn_checksum_t *checksum;
  const char *hex_digest;

  /* For non-switch operations, follow link_path in the target. */
  if (info && info->link_path && !b->is_switch)
    {
      t_path = info->link_path;
      SVN_ERR(fake_dirent(&t_entry, b->t_root, t_path, pool));
    }

  if (info && !SVN_IS_VALID_REVNUM(info->rev))
    {
      /* Delete this entry in the source. */
      s_path = NULL;
      s_entry = NULL;
    }
  else if (info && s_path)
    {
      /* Follow the rev and possibly path in this entry. */
      s_path = (info->link_path) ? info->link_path : s_path;
      s_rev = info->rev;
      SVN_ERR(get_source_root(b, &s_root, s_rev));
      SVN_ERR(fake_dirent(&s_entry, s_root, s_path, pool));
    }

  /* Don't let the report carry us somewhere nonexistent. */
  if (s_path && !s_entry)
    return svn_error_createf(SVN_ERR_FS_NOT_FOUND, NULL,
                             _("Working copy path '%s' does not exist in "
                               "repository"), e_path);

  /* If the source and target both exist and are of the same kind,
     then find out whether they're related.  If they're exactly the
     same, then we don't have to do anything (unless the report has
     changes to the source).  If we're ignoring ancestry, then any two
     nodes of the same type are related enough for us. */
  related = FALSE;
  if (s_entry && t_entry && s_entry->kind == t_entry->kind)
    {
      int distance = svn_fs_compare_ids(s_entry->id, t_entry->id);
      svn_boolean_t changed = TRUE;

      /* Check related files for content changes to avoid reporting
       * unchanged copies of files to the client as an open_file() call
       * and change_file_prop()/apply_textdelta() calls with no-op changes.
       * The client will otherwise raise unnecessary tree conflicts. */
      if (!b->ignore_ancestry && t_entry->kind == svn_node_file &&
          distance == 1)
        {
          if (s_root == NULL)
            SVN_ERR(get_source_root(b, &s_root, s_rev));

          SVN_ERR(svn_fs_props_changed(&changed, s_root, s_path,
                                       b->t_root, t_path, pool));
          if (!changed)
            SVN_ERR(svn_fs_contents_changed(&changed, s_root, s_path,
                                            b->t_root, t_path, pool));
        }

      if ((distance == 0 || !changed) && !any_path_info(b, e_path)
          && (requested_depth <= wc_depth || t_entry->kind == svn_node_file))
        {
          if (!info)
            return SVN_NO_ERROR;

          if (!info->start_empty)
            {
              svn_lock_t *lock;

              if (!info->lock_token)
                return SVN_NO_ERROR;

              SVN_ERR(svn_fs_get_lock(&lock, b->repos->fs, t_path, pool));
              if (lock && (strcmp(lock->token, info->lock_token) == 0))
                return SVN_NO_ERROR;
            }
        }

      related = (distance != -1 || b->ignore_ancestry);
    }

  /* If there's a source and it's not related to the target, nuke it. */
  if (s_entry && !related)
    {
      svn_revnum_t deleted_rev;

      SVN_ERR(svn_repos_deleted_rev(svn_fs_root_fs(b->t_root), t_path,
                                    s_rev, b->t_rev, &deleted_rev,
                                    pool));

      if (!SVN_IS_VALID_REVNUM(deleted_rev))
        {
          /* Two possibilities: either the thing doesn't exist in S_REV; or
             it wasn't deleted between S_REV and B->T_REV.  In the first case,
             I think we should leave DELETED_REV as SVN_INVALID_REVNUM, but
             in the second, it should be set to B->T_REV-1 for the call to
             delete_entry() below. */
          svn_node_kind_t kind;

          SVN_ERR(svn_fs_check_path(&kind, b->t_root, t_path, pool));
          if (kind != svn_node_none)
            deleted_rev = b->t_rev - 1;
        }

      SVN_ERR(b->editor->delete_entry(e_path, deleted_rev, dir_baton,
                                      pool));
      s_path = NULL;
    }

  /* If there's no target, we have nothing more to do. */
  if (!t_entry)
    return svn_error_trace(skip_path_info(b, e_path));

  /* Check if the user is authorized to find out about the target. */
  SVN_ERR(check_auth(b, &allowed, t_path, pool));
  if (!allowed)
    {
      if (t_entry->kind == svn_node_dir)
        SVN_ERR(b->editor->absent_directory(e_path, dir_baton, pool));
      else
        SVN_ERR(b->editor->absent_file(e_path, dir_baton, pool));
      return svn_error_trace(skip_path_info(b, e_path));
    }

  if (t_entry->kind == svn_node_dir)
    {
      if (related)
        SVN_ERR(b->editor->open_directory(e_path, dir_baton, s_rev, pool,
                                          &new_baton));
      else
        SVN_ERR(b->editor->add_directory(e_path, dir_baton, NULL,
                                         SVN_INVALID_REVNUM, pool,
                                         &new_baton));

      SVN_ERR(delta_dirs(b, s_rev, s_path, t_path, new_baton, e_path,
                         info ? info->start_empty : FALSE,
                         wc_depth, requested_depth, pool));
      return svn_error_trace(b->editor->close_directory(new_baton, pool));
    }
  else
    {
      if (related)
        {
          SVN_ERR(b->editor->open_file(e_path, dir_baton, s_rev, pool,
                                       &new_baton));
          SVN_ERR(delta_files(b, new_baton, s_rev, s_path, t_path,
                              info ? info->lock_token : NULL, pool));
        }
      else
        {
          svn_revnum_t copyfrom_rev = SVN_INVALID_REVNUM;
          const char *copyfrom_path = NULL;
          SVN_ERR(add_file_smartly(b, e_path, dir_baton, t_path, &new_baton,
                                   &copyfrom_path, &copyfrom_rev, pool));
          if (! copyfrom_path)
            /* Send txdelta between empty file (s_path@s_rev doesn't
               exist) and added file (t_path@t_root). */
            SVN_ERR(delta_files(b, new_baton, s_rev, s_path, t_path,
                                info ? info->lock_token : NULL, pool));
          else
            /* Send txdelta between copied file (copyfrom_path@copyfrom_rev)
               and added file (tpath@t_root). */
            SVN_ERR(delta_files(b, new_baton, copyfrom_rev, copyfrom_path,
                                t_path, info ? info->lock_token : NULL, pool));
        }

      SVN_ERR(svn_fs_file_checksum(&checksum, svn_checksum_md5, b->t_root,
                                   t_path, TRUE, pool));
      hex_digest = svn_checksum_to_cstring(checksum, pool);
      return svn_error_trace(b->editor->close_file(new_baton, hex_digest,
                                                   pool));
    }
}