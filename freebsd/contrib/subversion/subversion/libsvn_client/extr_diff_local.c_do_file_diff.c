#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_13__ {int /*<<< orphan*/  (* file_closed ) (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,TYPE_1__ const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* file_changed ) (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_3__*,void*,TYPE_1__ const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* file_added ) (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,TYPE_1__ const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* file_deleted ) (char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,void*,TYPE_1__ const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* file_opened ) (void**,scalar_t__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ svn_diff_tree_processor_t ;
typedef  int /*<<< orphan*/  svn_diff_source_t ;
struct TYPE_14__ {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  mimetypes_map; int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_2__ svn_client_ctx_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_15__ {scalar_t__ nelts; } ;
typedef  TYPE_3__ apr_array_header_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MIME_TYPE ; 
 int /*<<< orphan*/  get_props (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (void**,scalar_t__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,void*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_3__*,void*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_diff__source_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_dirent_skip_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/  svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_detect_mimetype2 (char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_files_contents_same_p (scalar_t__*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_prop_diffs (TYPE_3__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_string_create (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  translate_if_necessary (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
do_file_diff(const char *left_abspath,
             const char *right_abspath,
             const char *left_root_abspath,
             const char *right_root_abspath,
             svn_boolean_t left_only,
             svn_boolean_t right_only,
             void *parent_baton,
             const svn_diff_tree_processor_t *diff_processor,
             svn_client_ctx_t *ctx,
             apr_pool_t *scratch_pool)
{
  const char *relpath;
  svn_diff_source_t *left_source;
  svn_diff_source_t *right_source;
  svn_boolean_t skip = FALSE;
  apr_hash_t *left_props;
  apr_hash_t *right_props;
  void *file_baton;

  relpath = svn_dirent_skip_ancestor(left_root_abspath, left_abspath);

 if (! right_only)
    left_source = svn_diff__source_create(SVN_INVALID_REVNUM, scratch_pool);
  else
    left_source = NULL;

  if (! left_only)
    right_source = svn_diff__source_create(SVN_INVALID_REVNUM, scratch_pool);
  else
    right_source = NULL;

  SVN_ERR(diff_processor->file_opened(&file_baton, &skip,
                                      relpath,
                                      left_source,
                                      right_source,
                                      NULL /* copyfrom_source */,
                                      parent_baton,
                                      diff_processor,
                                      scratch_pool,
                                      scratch_pool));

  if (skip)
    return SVN_NO_ERROR;

   if (! right_only)
    {
      SVN_ERR(get_props(&left_props, left_abspath, ctx->wc_ctx,
                        scratch_pool, scratch_pool));

      /* We perform a mimetype detection to avoid diffing binary files
         for textual changes.*/
      if (! svn_hash_gets(left_props, SVN_PROP_MIME_TYPE))
        {
          const char *mime_type;

          /* ### Use libmagic magic? */
          SVN_ERR(svn_io_detect_mimetype2(&mime_type, left_abspath,
                                          ctx->mimetypes_map, scratch_pool));

          if (mime_type)
            svn_hash_sets(left_props, SVN_PROP_MIME_TYPE,
                          svn_string_create(mime_type, scratch_pool));
        }

      SVN_ERR(translate_if_necessary(&left_abspath, left_props,
                                     ctx->cancel_func, ctx->cancel_baton,
                                     scratch_pool, scratch_pool));
    }
  else
    left_props = NULL;

  if (! left_only)
    {
      SVN_ERR(get_props(&right_props, right_abspath, ctx->wc_ctx,
                        scratch_pool, scratch_pool));

      /* We perform a mimetype detection to avoid diffing binary files
         for textual changes.*/
      if (! svn_hash_gets(right_props, SVN_PROP_MIME_TYPE))
        {
          const char *mime_type;

          /* ### Use libmagic magic? */
          SVN_ERR(svn_io_detect_mimetype2(&mime_type, right_abspath,
                                          ctx->mimetypes_map, scratch_pool));

          if (mime_type)
            svn_hash_sets(right_props, SVN_PROP_MIME_TYPE,
                          svn_string_create(mime_type, scratch_pool));
        }

      SVN_ERR(translate_if_necessary(&right_abspath, right_props,
                                     ctx->cancel_func, ctx->cancel_baton,
                                     scratch_pool, scratch_pool));

    }
  else
    right_props = NULL;

  if (left_only)
    {
      SVN_ERR(diff_processor->file_deleted(relpath,
                                           left_source,
                                           left_abspath,
                                           left_props,
                                           file_baton,
                                           diff_processor,
                                           scratch_pool));
    }
  else if (right_only)
    {
      SVN_ERR(diff_processor->file_added(relpath,
                                         NULL /* copyfrom_source */,
                                         right_source,
                                         NULL /* copyfrom_file */,
                                         right_abspath,
                                         NULL /* copyfrom_props */,
                                         right_props,
                                         file_baton,
                                         diff_processor,
                                         scratch_pool));
    }
  else
    {
      /* ### Perform diff -> close/changed */
      svn_boolean_t same;
      apr_array_header_t *prop_changes;

      SVN_ERR(svn_io_files_contents_same_p(&same, left_abspath, right_abspath,
                                           scratch_pool));

      SVN_ERR(svn_prop_diffs(&prop_changes, right_props, left_props,
                             scratch_pool));

      if (!same || prop_changes->nelts > 0)
        {
          SVN_ERR(diff_processor->file_changed(relpath,
                                               left_source,
                                               right_source,
                                               same ? NULL : left_abspath,
                                               same ? NULL : right_abspath,
                                               left_props,
                                               right_props,
                                               !same,
                                               prop_changes,
                                               file_baton,
                                               diff_processor,
                                               scratch_pool));
        }
      else
        {
          SVN_ERR(diff_processor->file_closed(relpath,
                                            left_source,
                                            right_source,
                                            file_baton,
                                            diff_processor,
                                            scratch_pool));
        }
    }
  return SVN_NO_ERROR;
}