#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char const* path; int /*<<< orphan*/ * rev_props; scalar_t__ revision; int /*<<< orphan*/  lock_state; int /*<<< orphan*/  prop_state; int /*<<< orphan*/  content_state; int /*<<< orphan*/  kind; } ;
typedef  TYPE_3__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  svn_txdelta_window_handler_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct rev {int dummy; } ;
struct file_rev_baton {int /*<<< orphan*/ * currpool; TYPE_2__* last_rev; int /*<<< orphan*/ * mainpool; scalar_t__ include_merged_revisions; int /*<<< orphan*/ * last_filename; int /*<<< orphan*/  start_rev; int /*<<< orphan*/  end_rev; void* last_props; scalar_t__ last_revnum; scalar_t__ backwards; int /*<<< orphan*/ * filepool; TYPE_1__* ctx; int /*<<< orphan*/  repos_root_url; int /*<<< orphan*/  target; scalar_t__ check_mime_type; } ;
struct delta_baton {int /*<<< orphan*/  wrapped_baton; int /*<<< orphan*/  wrapped_handler; TYPE_2__* rev; scalar_t__ is_merged_revision; struct file_rev_baton* file_rev_baton; int /*<<< orphan*/  filename; int /*<<< orphan*/ * source_stream; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_7__ {int /*<<< orphan*/  path; scalar_t__ revision; void* rev_props; } ;
struct TYPE_6__ {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  (* cancel_func ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_CLIENT_IS_BINARY_FILE ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MIME_TYPE ; 
 int /*<<< orphan*/  _ (char*) ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_local_style (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_del_on_pool_cleanup ; 
 scalar_t__ svn_mime_type_is_binary (char const*) ; 
 int /*<<< orphan*/  svn_node_none ; 
 scalar_t__ svn_path_is_url (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_path_url_add_component2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_prop_array_to_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_prop_get_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* svn_prop_hash_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_copy3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_disown (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_readonly (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_unique (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_txdelta_apply (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_wc_create_notify_url (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_blame_revision ; 
 int /*<<< orphan*/  svn_wc_notify_lock_state_inapplicable ; 
 int /*<<< orphan*/  svn_wc_notify_state_inapplicable ; 
 int /*<<< orphan*/  update_blame (struct delta_baton*) ; 
 int /*<<< orphan*/  window_handler ; 

__attribute__((used)) static svn_error_t *
file_rev_handler(void *baton, const char *path, svn_revnum_t revnum,
                 apr_hash_t *rev_props,
                 svn_boolean_t merged_revision,
                 svn_txdelta_window_handler_t *content_delta_handler,
                 void **content_delta_baton,
                 apr_array_header_t *prop_diffs,
                 apr_pool_t *pool)
{
  struct file_rev_baton *frb = baton;
  svn_stream_t *last_stream;
  svn_stream_t *cur_stream;
  struct delta_baton *delta_baton;
  apr_pool_t *filepool;

  /* Clear the current pool. */
  svn_pool_clear(frb->currpool);

  if (frb->check_mime_type)
    {
      apr_hash_t *props = svn_prop_array_to_hash(prop_diffs, frb->currpool);
      const char *value;

      frb->check_mime_type = FALSE; /* Only check first */

      value = svn_prop_get_value(props, SVN_PROP_MIME_TYPE);

      if (value && svn_mime_type_is_binary(value))
        {
          return svn_error_createf(
              SVN_ERR_CLIENT_IS_BINARY_FILE, NULL,
              _("Cannot calculate blame information for binary file '%s'"),
               (svn_path_is_url(frb->target)
                      ? frb->target 
                      : svn_dirent_local_style(frb->target, pool)));
        }
    }

  if (frb->ctx->notify_func2)
    {
      svn_wc_notify_t *notify
            = svn_wc_create_notify_url(
                            svn_path_url_add_component2(frb->repos_root_url,
                                                        path+1, pool),
                            svn_wc_notify_blame_revision, pool);
      notify->path = path;
      notify->kind = svn_node_none;
      notify->content_state = notify->prop_state
        = svn_wc_notify_state_inapplicable;
      notify->lock_state = svn_wc_notify_lock_state_inapplicable;
      notify->revision = revnum;
      notify->rev_props = rev_props;
      frb->ctx->notify_func2(frb->ctx->notify_baton2, notify, pool);
    }

  if (frb->ctx->cancel_func)
    SVN_ERR(frb->ctx->cancel_func(frb->ctx->cancel_baton));

  /* If there were no content changes and no (potential) merges, we couldn't
     care less about this revision now.  Note that we checked the mime type
     above, so things work if the user just changes the mime type in a commit.
     Also note that we don't switch the pools in this case.  This is important,
     since the tempfile will be removed by the pool and we need the tempfile
     from the last revision with content changes. */
  if (!content_delta_handler
      && (!frb->include_merged_revisions || merged_revision))
    return SVN_NO_ERROR;

  /* Create delta baton. */
  delta_baton = apr_pcalloc(frb->currpool, sizeof(*delta_baton));

  /* Prepare the text delta window handler. */
  if (frb->last_filename)
    SVN_ERR(svn_stream_open_readonly(&delta_baton->source_stream, frb->last_filename,
                                     frb->currpool, pool));
  else
    /* Means empty stream below. */
    delta_baton->source_stream = NULL;
  last_stream = svn_stream_disown(delta_baton->source_stream, pool);

  if (frb->include_merged_revisions && !merged_revision)
    filepool = frb->filepool;
  else
    filepool = frb->currpool;

  SVN_ERR(svn_stream_open_unique(&cur_stream, &delta_baton->filename, NULL,
                                 svn_io_file_del_on_pool_cleanup,
                                 filepool, filepool));

  /* Wrap the window handler with our own. */
  delta_baton->file_rev_baton = frb;
  delta_baton->is_merged_revision = merged_revision;

  /* Create the rev structure. */
  delta_baton->rev = apr_pcalloc(frb->mainpool, sizeof(struct rev));

  if (frb->backwards)
    {
      /* Use from last round...
         SVN_INVALID_REVNUM on first, which is exactly
         what we want */
      delta_baton->rev->revision = frb->last_revnum;
      delta_baton->rev->rev_props = frb->last_props;

      /* Store for next delta */
      if (revnum >= MIN(frb->start_rev, frb->end_rev))
        {
          frb->last_revnum = revnum;
          frb->last_props = svn_prop_hash_dup(rev_props, frb->mainpool);
        }
      /* Else: Not needed on last rev */
    }
  else if (merged_revision
           || (revnum >= MIN(frb->start_rev, frb->end_rev)))
    {
      /* 1+ for the "youngest to oldest" blame */
      SVN_ERR_ASSERT(revnum <= 1 + MAX(frb->end_rev, frb->start_rev));

      /* Set values from revision props. */
      delta_baton->rev->revision = revnum;
      delta_baton->rev->rev_props = svn_prop_hash_dup(rev_props, frb->mainpool);
    }
  else
    {
      /* We shouldn't get more than one revision outside the
         specified range (unless we alsoe receive merged revisions) */
      SVN_ERR_ASSERT((frb->last_filename == NULL)
                     || frb->include_merged_revisions);

      /* The file existed before start_rev; generate no blame info for
         lines from this revision (or before). 

         This revision specifies the state as it was at the start revision */

      delta_baton->rev->revision = SVN_INVALID_REVNUM;
    }

  if (frb->include_merged_revisions)
    delta_baton->rev->path = apr_pstrdup(frb->mainpool, path);

  /* Keep last revision for postprocessing after all changes */
  frb->last_rev = delta_baton->rev;

  /* Handle all delta - even if it is empty.
     We must do the latter to "merge" blame info from other branches. */
  if (content_delta_handler)
    {
      /* Proper delta - get window handler for applying delta.
         svn_ra_get_file_revs2 will drive the delta editor. */
      svn_txdelta_apply(last_stream, cur_stream, NULL, NULL,
                        frb->currpool,
                        &delta_baton->wrapped_handler,
                        &delta_baton->wrapped_baton);
      *content_delta_handler = window_handler;
      *content_delta_baton = delta_baton;
    }
  else
    {
      /* Apply an empty delta, i.e. simply copy the old contents.
         We can't simply use the existing file due to the pool rotation logic.
         Trigger the blame update magic. */
      SVN_ERR(svn_stream_copy3(last_stream, cur_stream, NULL, NULL, pool));
      SVN_ERR(update_blame(delta_baton));
    }

  return SVN_NO_ERROR;
}