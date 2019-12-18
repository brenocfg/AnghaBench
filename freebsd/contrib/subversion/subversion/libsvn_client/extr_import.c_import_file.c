#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {char const* mime_type; int /*<<< orphan*/  lock_state; int /*<<< orphan*/  prop_state; int /*<<< orphan*/  content_state; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  svn_string_t ;
struct TYPE_15__ {scalar_t__ special; } ;
typedef  TYPE_2__ svn_io_dirent2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_16__ {int /*<<< orphan*/  (* close_file ) (void*,char const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* change_file_prop ) (void*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* add_file ) (char const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ;} ;
typedef  TYPE_3__ svn_delta_editor_t ;
struct TYPE_17__ {int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_4__ svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
struct TYPE_18__ {int /*<<< orphan*/  autoprops; int /*<<< orphan*/  magic_cookie; int /*<<< orphan*/  repos_changed; } ;
typedef  TYPE_5__ import_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  SVN_PROP_BOOLEAN_TRUE ; 
 char const* SVN_PROP_SPECIAL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_file_contents (int /*<<< orphan*/ **,char const*,void*,TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (char const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  stub2 (void*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (void*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (void*,char const*,int /*<<< orphan*/ *) ; 
 char* svn_checksum_to_cstring (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__get_paths_auto_props (int /*<<< orphan*/ **,char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_node_file ; 
 int /*<<< orphan*/  svn_path_check_valid (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_string_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_commit_added ; 
 int /*<<< orphan*/  svn_wc_notify_lock_state_inapplicable ; 
 int /*<<< orphan*/  svn_wc_notify_state_inapplicable ; 

__attribute__((used)) static svn_error_t *
import_file(const svn_delta_editor_t *editor,
            void *dir_baton,
            const char *local_abspath,
            const char *edit_path,
            const svn_io_dirent2_t *dirent,
            import_ctx_t *import_ctx,
            svn_client_ctx_t *ctx,
            apr_pool_t *pool)
{
  void *file_baton;
  const char *mimetype = NULL;
  svn_checksum_t *result_md5_checksum;
  const char *text_checksum;
  apr_hash_t* properties;
  apr_hash_index_t *hi;

  SVN_ERR(svn_path_check_valid(local_abspath, pool));

  /* Add the file, using the pool from the FILES hash. */
  SVN_ERR(editor->add_file(edit_path, dir_baton, NULL, SVN_INVALID_REVNUM,
                           pool, &file_baton));

  /* Remember that the repository was modified */
  import_ctx->repos_changed = TRUE;

  if (! dirent->special)
    {
      /* add automatic properties */
      SVN_ERR(svn_client__get_paths_auto_props(&properties, &mimetype,
                                               local_abspath,
                                               import_ctx->magic_cookie,
                                               import_ctx->autoprops,
                                               ctx, pool, pool));
    }
  else
    properties = apr_hash_make(pool);

  if (properties)
    {
      for (hi = apr_hash_first(pool, properties); hi; hi = apr_hash_next(hi))
        {
          const char *pname = apr_hash_this_key(hi);
          const svn_string_t *pval = apr_hash_this_val(hi);

          SVN_ERR(editor->change_file_prop(file_baton, pname, pval, pool));
        }
    }

  if (ctx->notify_func2)
    {
      svn_wc_notify_t *notify
        = svn_wc_create_notify(local_abspath, svn_wc_notify_commit_added,
                               pool);
      notify->kind = svn_node_file;
      notify->mime_type = mimetype;
      notify->content_state = notify->prop_state
        = svn_wc_notify_state_inapplicable;
      notify->lock_state = svn_wc_notify_lock_state_inapplicable;
      ctx->notify_func2(ctx->notify_baton2, notify, pool);
    }

  /* If this is a special file, we need to set the svn:special
     property and create a temporary detranslated version in order to
     send to the server. */
  if (dirent->special)
    {
      svn_hash_sets(properties, SVN_PROP_SPECIAL,
                    svn_string_create(SVN_PROP_BOOLEAN_TRUE, pool));
      SVN_ERR(editor->change_file_prop(file_baton, SVN_PROP_SPECIAL,
                                       svn_hash_gets(properties,
                                                     SVN_PROP_SPECIAL),
                                       pool));
    }

  /* Now, transmit the file contents. */
  SVN_ERR(send_file_contents(&result_md5_checksum, local_abspath,
                             file_baton, editor, properties, pool));

  /* Finally, close the file. */
  text_checksum = svn_checksum_to_cstring(result_md5_checksum, pool);
  return svn_error_trace(editor->close_file(file_baton, text_checksum, pool));
}