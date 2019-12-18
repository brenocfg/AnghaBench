#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct context {TYPE_1__* editor; int /*<<< orphan*/  target_root; int /*<<< orphan*/  source_root; int /*<<< orphan*/  authz_read_baton; int /*<<< orphan*/  (* authz_read_func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/ * (* close_file ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* open_file ) (char const*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ;int /*<<< orphan*/ * (* close_directory ) (void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* open_directory ) (char const*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MAYBE_DEMOTE_DEPTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * absent_file_or_dir (struct context*,void*,char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delta_dirs (struct context*,void*,int /*<<< orphan*/ ,char const*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delta_files (struct context*,void*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_path_revision (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (char const*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * stub3 (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (char const*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * stub5 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/  svn_checksum_to_cstring (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_file_checksum (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 

__attribute__((used)) static svn_error_t *
replace_file_or_dir(struct context *c,
                    void *dir_baton,
                    svn_depth_t depth,
                    const char *source_path,
                    const char *target_path,
                    const char *edit_path,
                    svn_node_kind_t tgt_kind,
                    apr_pool_t *pool)
{
  svn_revnum_t base_revision = SVN_INVALID_REVNUM;
  svn_boolean_t allowed;

  SVN_ERR_ASSERT(target_path && source_path && edit_path);

  if (c->authz_read_func)
    {
      SVN_ERR(c->authz_read_func(&allowed, c->target_root, target_path,
                                 c->authz_read_baton, pool));
      if (!allowed)
        return absent_file_or_dir(c, dir_baton, edit_path, tgt_kind, pool);
    }

  /* Get the base revision for the entry from the hash. */
  base_revision = get_path_revision(c->source_root, source_path, pool);

  if (tgt_kind == svn_node_dir)
    {
      void *subdir_baton;

      SVN_ERR(c->editor->open_directory(edit_path, dir_baton,
                                        base_revision, pool,
                                        &subdir_baton));
      SVN_ERR(delta_dirs(c, subdir_baton, MAYBE_DEMOTE_DEPTH(depth),
                         source_path, target_path, edit_path, pool));
      return c->editor->close_directory(subdir_baton, pool);
    }
  else
    {
      void *file_baton;
      svn_checksum_t *checksum;

      SVN_ERR(c->editor->open_file(edit_path, dir_baton, base_revision,
                                   pool, &file_baton));
      SVN_ERR(delta_files(c, file_baton, source_path, target_path, pool));
      SVN_ERR(svn_fs_file_checksum(&checksum, svn_checksum_md5,
                                   c->target_root, target_path, TRUE,
                                   pool));
      return c->editor->close_file
             (file_baton, svn_checksum_to_cstring(checksum, pool), pool);
    }
}