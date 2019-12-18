#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_txdelta_window_handler_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {void* baton; } ;
struct editor_baton {TYPE_2__* deditor; scalar_t__ repos_root; TYPE_1__ root; int /*<<< orphan*/  changes; int /*<<< orphan*/  base_relpath; } ;
struct change_node {scalar_t__ action; scalar_t__ kind; char* copyfrom_path; int /*<<< orphan*/  checksum; scalar_t__ contents_abspath; scalar_t__ contents_changed; int /*<<< orphan*/  changing; int /*<<< orphan*/  copyfrom_rev; int /*<<< orphan*/  deleting; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* close_file ) (void*,char const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* apply_textdelta ) (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ;int /*<<< orphan*/  (* open_file ) (char const*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ;int /*<<< orphan*/  (* open_directory ) (char const*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ;int /*<<< orphan*/  (* add_file ) (char const*,void*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ;int /*<<< orphan*/  (* add_directory ) (char const*,void*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ;int /*<<< orphan*/  (* delete_entry ) (char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* absent_file ) (char const*,void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* absent_directory ) (char const*,void*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ RESTRUCTURE_ADD ; 
 scalar_t__ RESTRUCTURE_ADD_ABSENT ; 
 scalar_t__ RESTRUCTURE_DELETE ; 
 scalar_t__ RESTRUCTURE_NONE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 char* apr_pstrcat (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drive_ev1_props (struct editor_baton const*,char const*,struct change_node const*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub10 (void*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (char const*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (char const*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (char const*,void*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  stub6 (char const*,void*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  stub7 (char const*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  stub8 (char const*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  stub9 (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 char* svn_checksum_to_cstring (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct change_node* svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_unknown ; 
 char* svn_path_url_add_component2 (scalar_t__,char*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_readonly (int /*<<< orphan*/ **,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_txdelta_send_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
apply_change(void **dir_baton,
             void *parent_baton,
             void *callback_baton,
             const char *ev1_relpath,
             apr_pool_t *result_pool)
{
  /* ### fix this?  */
  apr_pool_t *scratch_pool = result_pool;
  const struct editor_baton *eb = callback_baton;
  const struct change_node *change;
  const char *relpath;
  void *file_baton = NULL;

  /* Typically, we are not creating new directory batons.  */
  *dir_baton = NULL;

  relpath = svn_relpath_join(eb->base_relpath, ev1_relpath, scratch_pool);
  change = svn_hash_gets(eb->changes, relpath);

  /* The callback should only be called for paths in CHANGES.  */
  SVN_ERR_ASSERT(change != NULL);

  /* Are we editing the root of the tree?  */
  if (parent_baton == NULL)
    {
      /* The root was opened in start_edit_func()  */
      *dir_baton = eb->root.baton;

      /* Only property edits are allowed on the root.  */
      SVN_ERR_ASSERT(change->action == RESTRUCTURE_NONE);
      SVN_ERR(drive_ev1_props(eb, relpath, change, *dir_baton, scratch_pool));

      /* No further action possible for the root.  */
      return SVN_NO_ERROR;
    }

  if (change->action == RESTRUCTURE_DELETE)
    {
      SVN_ERR(eb->deditor->delete_entry(ev1_relpath, change->deleting,
                                        parent_baton, scratch_pool));

      /* No futher action possible for this node.  */
      return SVN_NO_ERROR;
    }

  /* If we're not deleting this node, then we should know its kind.  */
  SVN_ERR_ASSERT(change->kind != svn_node_unknown);

  if (change->action == RESTRUCTURE_ADD_ABSENT)
    {
      if (change->kind == svn_node_dir)
        SVN_ERR(eb->deditor->absent_directory(ev1_relpath, parent_baton,
                                              scratch_pool));
      else
        SVN_ERR(eb->deditor->absent_file(ev1_relpath, parent_baton,
                                         scratch_pool));

      /* No further action possible for this node.  */
      return SVN_NO_ERROR;
    }
  /* RESTRUCTURE_NONE or RESTRUCTURE_ADD  */

  if (change->action == RESTRUCTURE_ADD)
    {
      const char *copyfrom_url = NULL;
      svn_revnum_t copyfrom_rev = SVN_INVALID_REVNUM;

      /* Do we have an old node to delete first?  */
      if (SVN_IS_VALID_REVNUM(change->deleting))
        SVN_ERR(eb->deditor->delete_entry(ev1_relpath, change->deleting,
                                          parent_baton, scratch_pool));

      /* Are we copying the node from somewhere?  */
      if (change->copyfrom_path)
        {
          if (eb->repos_root)
            copyfrom_url = svn_path_url_add_component2(eb->repos_root,
                                                       change->copyfrom_path,
                                                       scratch_pool);
          else
            {
              copyfrom_url = change->copyfrom_path;

              /* Make this an FS path by prepending "/" */
              if (copyfrom_url[0] != '/')
                copyfrom_url = apr_pstrcat(scratch_pool, "/",
                                           copyfrom_url, SVN_VA_NULL);
            }

          copyfrom_rev = change->copyfrom_rev;
        }

      if (change->kind == svn_node_dir)
        SVN_ERR(eb->deditor->add_directory(ev1_relpath, parent_baton,
                                           copyfrom_url, copyfrom_rev,
                                           result_pool, dir_baton));
      else
        SVN_ERR(eb->deditor->add_file(ev1_relpath, parent_baton,
                                      copyfrom_url, copyfrom_rev,
                                      result_pool, &file_baton));
    }
  else
    {
      if (change->kind == svn_node_dir)
        SVN_ERR(eb->deditor->open_directory(ev1_relpath, parent_baton,
                                            change->changing,
                                            result_pool, dir_baton));
      else
        SVN_ERR(eb->deditor->open_file(ev1_relpath, parent_baton,
                                       change->changing,
                                       result_pool, &file_baton));
    }

  /* Apply any properties in CHANGE to the node.  */
  if (change->kind == svn_node_dir)
    SVN_ERR(drive_ev1_props(eb, relpath, change, *dir_baton, scratch_pool));
  else
    SVN_ERR(drive_ev1_props(eb, relpath, change, file_baton, scratch_pool));

  if (change->contents_changed && change->contents_abspath)
    {
      svn_txdelta_window_handler_t handler;
      void *handler_baton;
      svn_stream_t *contents;

      /* ### would be nice to have a BASE_CHECKSUM, but hey: this is the
         ### shim code...  */
      SVN_ERR(eb->deditor->apply_textdelta(file_baton, NULL, scratch_pool,
                                           &handler, &handler_baton));
      SVN_ERR(svn_stream_open_readonly(&contents, change->contents_abspath,
                                       scratch_pool, scratch_pool));
      /* ### it would be nice to send a true txdelta here, but whatever.  */
      SVN_ERR(svn_txdelta_send_stream(contents, handler, handler_baton,
                                      NULL, scratch_pool));
      SVN_ERR(svn_stream_close(contents));
    }

  if (file_baton)
    {
      const char *digest = svn_checksum_to_cstring(change->checksum,
                                                   scratch_pool);

      SVN_ERR(eb->deditor->close_file(file_baton, digest, scratch_pool));
    }

  return SVN_NO_ERROR;
}