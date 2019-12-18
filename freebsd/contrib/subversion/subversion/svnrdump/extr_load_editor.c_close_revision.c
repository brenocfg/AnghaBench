#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* close_edit ) (void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* close_directory ) (void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* open_root ) (void*,scalar_t__,int /*<<< orphan*/ ,void**) ;} ;
typedef  TYPE_3__ svn_delta_editor_t ;
struct revision_baton {scalar_t__ rev; int rev_offset; int /*<<< orphan*/  pool; int /*<<< orphan*/  author; TYPE_2__* pb; int /*<<< orphan*/  datestamp; int /*<<< orphan*/  revprop_table; TYPE_1__* db; } ;
struct TYPE_6__ {int /*<<< orphan*/  session; int /*<<< orphan*/  skip_revprops; int /*<<< orphan*/  rev_map; int /*<<< orphan*/  quiet; void* commit_edit_baton; TYPE_3__* commit_editor; } ;
struct TYPE_5__ {void* baton; struct TYPE_5__* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 scalar_t__ SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_AUTHOR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_DATE ; 
 int /*<<< orphan*/  commit_callback ; 
 scalar_t__ get_revision_mapping (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (void*,scalar_t__,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  stub5 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_cmdline_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svn_hash_gets (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_change_rev_prop2 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_get_commit_editor3 (int /*<<< orphan*/ ,TYPE_3__ const**,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_repos__validate_prop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
close_revision(void *baton)
{
  struct revision_baton *rb = baton;
  const svn_delta_editor_t *commit_editor = rb->pb->commit_editor;
  void *commit_edit_baton = rb->pb->commit_edit_baton;
  svn_revnum_t committed_rev = SVN_INVALID_REVNUM;

  /* Fake revision 0 */
  if (rb->rev == 0)
    {
      /* ### Don't print directly; generate a notification. */
      if (! rb->pb->quiet)
        SVN_ERR(svn_cmdline_printf(rb->pool, "* Loaded revision 0.\n"));
    }
  else if (commit_editor)
    {
      /* Close all pending open directories, and then close the edit
         session itself */
      while (rb->db && rb->db->parent)
        {
          SVN_ERR(commit_editor->close_directory(rb->db->baton, rb->pool));
          rb->db = rb->db->parent;
        }
      /* root dir's baton */
      SVN_ERR(commit_editor->close_directory(rb->db->baton, rb->pool));
      SVN_ERR(commit_editor->close_edit(commit_edit_baton, rb->pool));
    }
  else
    {
      svn_revnum_t head_rev_before_commit = rb->rev - rb->rev_offset - 1;
      void *child_baton;

      /* Legitimate revision with no node information */
      SVN_ERR(svn_ra_get_commit_editor3(rb->pb->session, &commit_editor,
                                        &commit_edit_baton, rb->revprop_table,
                                        commit_callback, baton,
                                        NULL, FALSE, rb->pool));

      SVN_ERR(commit_editor->open_root(commit_edit_baton,
                                       head_rev_before_commit,
                                       rb->pool, &child_baton));

      SVN_ERR(commit_editor->close_directory(child_baton, rb->pool));
      SVN_ERR(commit_editor->close_edit(commit_edit_baton, rb->pool));
    }

  /* svn_fs_commit_txn() rewrites the datestamp and author properties;
     we'll rewrite them again by hand after closing the commit_editor.
     The only time we don't do this is for revision 0 when loaded into
     a non-empty repository.  */
  if (rb->rev > 0)
    {
      committed_rev = get_revision_mapping(rb->pb->rev_map, rb->rev);
    }
  else if (rb->rev_offset == -1)
    {
      committed_rev = 0;
    }

  if (SVN_IS_VALID_REVNUM(committed_rev))
    {
      if (!svn_hash_gets(rb->pb->skip_revprops, SVN_PROP_REVISION_DATE))
        {
          SVN_ERR(svn_repos__validate_prop(SVN_PROP_REVISION_DATE,
                                           rb->datestamp, rb->pool));
          SVN_ERR(svn_ra_change_rev_prop2(rb->pb->session, committed_rev,
                                          SVN_PROP_REVISION_DATE,
                                          NULL, rb->datestamp, rb->pool));
        }
      if (!svn_hash_gets(rb->pb->skip_revprops, SVN_PROP_REVISION_AUTHOR))
        {
          SVN_ERR(svn_repos__validate_prop(SVN_PROP_REVISION_AUTHOR,
                                           rb->author, rb->pool));
          SVN_ERR(svn_ra_change_rev_prop2(rb->pb->session, committed_rev,
                                          SVN_PROP_REVISION_AUTHOR,
                                          NULL, rb->author, rb->pool));
        }
    }

  svn_pool_destroy(rb->pool);

  return SVN_NO_ERROR;
}