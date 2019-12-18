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
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_notify_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_16__ {int /*<<< orphan*/ * (* abort_edit ) (void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* close_edit ) (void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* open_root ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ;} ;
typedef  TYPE_1__ svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_commit_callback2_t ;
typedef  int /*<<< orphan*/  svn_client_commit_item3_t ;
struct TYPE_17__ {int /*<<< orphan*/  pool; TYPE_4__* ctx; int /*<<< orphan*/  base_revision; TYPE_10__* root_op; int /*<<< orphan*/  ra_session; } ;
typedef  TYPE_2__ svn_client__mtcc_t ;
typedef  int /*<<< orphan*/  item ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_18__ {int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_15__ {scalar_t__ kind; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MTCC_UNMODIFIED (TYPE_2__*) ; 
 scalar_t__ OP_OPEN_DIR ; 
 scalar_t__ SVN_CLIENT__HAS_LOG_MSG_FUNC (TYPE_4__*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_DIRECTORY ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * add_commit_items (TYPE_10__*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * commit_directory (TYPE_1__ const*,TYPE_10__*,char*,int /*<<< orphan*/ ,void*,char const*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mtcc_reparent (char const*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub3 (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub4 (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client__ensure_revprop_table (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client__get_log_msg (char const**,char const**,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client_open_ra_session2 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_ra_check_path (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_get_commit_editor3 (int /*<<< orphan*/ ,TYPE_1__ const**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_ra_get_session_url (int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_reparent (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_uri_split (char const**,char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc_create_notify_url (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_commit_finalizing ; 

svn_error_t *
svn_client__mtcc_commit(apr_hash_t *revprop_table,
                        svn_commit_callback2_t commit_callback,
                        void *commit_baton,
                        svn_client__mtcc_t *mtcc,
                        apr_pool_t *scratch_pool)
{
  const svn_delta_editor_t *editor;
  void *edit_baton;
  void *root_baton;
  apr_hash_t *commit_revprops;
  svn_node_kind_t kind;
  svn_error_t *err;
  const char *session_url;
  const char *log_msg;

  if (MTCC_UNMODIFIED(mtcc))
    {
      /* No changes -> no revision. Easy out */
      svn_pool_destroy(mtcc->pool);
      return SVN_NO_ERROR;
    }

  SVN_ERR(svn_ra_get_session_url(mtcc->ra_session, &session_url, scratch_pool));

  if (mtcc->root_op->kind != OP_OPEN_DIR)
    {
      const char *name;

      svn_uri_split(&session_url, &name, session_url, scratch_pool);

      if (*name)
        {
          SVN_ERR(mtcc_reparent(session_url, mtcc, scratch_pool));

          SVN_ERR(svn_ra_reparent(mtcc->ra_session, session_url, scratch_pool));
        }
    }

    /* Create new commit items and add them to the array. */
  if (SVN_CLIENT__HAS_LOG_MSG_FUNC(mtcc->ctx))
    {
      svn_client_commit_item3_t *item;
      const char *tmp_file;
      apr_array_header_t *commit_items
                = apr_array_make(scratch_pool, 32, sizeof(item));

      SVN_ERR(add_commit_items(mtcc->root_op, session_url, session_url,
                               commit_items, scratch_pool, scratch_pool));

      SVN_ERR(svn_client__get_log_msg(&log_msg, &tmp_file, commit_items,
                                      mtcc->ctx, scratch_pool));

      if (! log_msg)
        return SVN_NO_ERROR;
    }
  else
    log_msg = "";

  SVN_ERR(svn_client__ensure_revprop_table(&commit_revprops, revprop_table,
                                           log_msg, mtcc->ctx, scratch_pool));

  /* Ugly corner case: The ra session might have died while we were waiting
     for the callback */

  err = svn_ra_check_path(mtcc->ra_session, "", mtcc->base_revision, &kind,
                          scratch_pool);

  if (err)
    {
      svn_error_t *err2 = svn_client_open_ra_session2(&mtcc->ra_session,
                                                      session_url,
                                                      NULL, mtcc->ctx,
                                                      mtcc->pool,
                                                      scratch_pool);

      if (err2)
        {
          svn_pool_destroy(mtcc->pool);
          return svn_error_trace(svn_error_compose_create(err, err2));
        }
      svn_error_clear(err);

      SVN_ERR(svn_ra_check_path(mtcc->ra_session, "",
                                mtcc->base_revision, &kind, scratch_pool));
    }

  if (kind != svn_node_dir)
    return svn_error_createf(SVN_ERR_FS_NOT_DIRECTORY, NULL,
                             _("Can't commit to '%s' because it "
                               "is not a directory"),
                             session_url);

  /* Beware that the editor object must not live longer than the MTCC.
     Otherwise, txn objects etc. in EDITOR may live longer than their
     respective FS objects.  So, we can't use SCRATCH_POOL here. */
  SVN_ERR(svn_ra_get_commit_editor3(mtcc->ra_session, &editor, &edit_baton,
                                    commit_revprops,
                                    commit_callback, commit_baton,
                                    NULL /* lock_tokens */,
                                    FALSE /* keep_locks */,
                                    mtcc->pool));

  err = editor->open_root(edit_baton, mtcc->base_revision, scratch_pool, &root_baton);

  if (!err)
    err = commit_directory(editor, mtcc->root_op, "", mtcc->base_revision,
                           root_baton, session_url, mtcc->ctx, scratch_pool);

  if (!err)
    {
      if (mtcc->ctx->notify_func2)
        {
          svn_wc_notify_t *notify;
          notify = svn_wc_create_notify_url(session_url,
                                            svn_wc_notify_commit_finalizing,
                                            scratch_pool);
          mtcc->ctx->notify_func2(mtcc->ctx->notify_baton2, notify,
                                  scratch_pool);
        }
      SVN_ERR(editor->close_edit(edit_baton, scratch_pool));
    }
  else
    err = svn_error_compose_create(err,
                                   editor->abort_edit(edit_baton, scratch_pool));

  svn_pool_destroy(mtcc->pool);

  return svn_error_trace(err);
}