#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_11__ {TYPE_3__* priv; } ;
typedef  TYPE_2__ svn_ra_session_t ;
struct TYPE_12__ {scalar_t__ bulk_updates; scalar_t__ supports_inline_props; scalar_t__ server_allows_bulk; } ;
typedef  TYPE_3__ svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  svn_ra_reporter3_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  void* svn_boolean_t ;
struct TYPE_13__ {char const* source; char const* destination; char const* update_target; int /*<<< orphan*/  body_template; void* send_copyfrom_args; void* ignore_ancestry; int /*<<< orphan*/  target_rev; int /*<<< orphan*/  body; int /*<<< orphan*/ * pool; void* done; void* editor_baton; int /*<<< orphan*/  const* editor; int /*<<< orphan*/  switched_paths; void* text_deltas; TYPE_3__* sess; } ;
typedef  TYPE_4__ report_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_RA_CAPABILITY_DEPTH ; 
 int /*<<< orphan*/  SVN_RA_SERF__REQUEST_BODY_IN_MEM_SIZE ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 int /*<<< orphan*/  SVN_XML_NAMESPACE ; 
 void* TRUE ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 char* apr_ltoa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ apr_strnatcasecmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  make_simple_xml_tag (TYPE_1__**,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ra_serf_reporter ; 
 int /*<<< orphan*/  svn_delta_depth_filter_editor (int /*<<< orphan*/  const**,void**,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_empty ; 
 int /*<<< orphan*/  svn_depth_files ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 char* svn_depth_to_word (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_serf__has_capability (TYPE_2__*,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__request_body_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__request_body_get_stream (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_tristate_false ; 
 scalar_t__ svn_tristate_true ; 
 int /*<<< orphan*/  svn_xml_make_open_tag (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  svn_xml_normal ; 

__attribute__((used)) static svn_error_t *
make_update_reporter(svn_ra_session_t *ra_session,
                     const svn_ra_reporter3_t **reporter,
                     void **report_baton,
                     svn_revnum_t revision,
                     const char *src_path,
                     const char *dest_path,
                     const char *update_target,
                     svn_depth_t depth,
                     svn_boolean_t ignore_ancestry,
                     svn_boolean_t text_deltas,
                     svn_boolean_t send_copyfrom_args,
                     const svn_delta_editor_t *update_editor,
                     void *update_baton,
                     apr_pool_t *result_pool,
                     apr_pool_t *scratch_pool)
{
  report_context_t *report;
  const svn_delta_editor_t *filter_editor;
  void *filter_baton;
  svn_boolean_t has_target = *update_target != '\0';
  svn_boolean_t server_supports_depth;
  svn_ra_serf__session_t *sess = ra_session->priv;
  svn_stringbuf_t *buf = NULL;
  svn_boolean_t use_bulk_updates;

  SVN_ERR(svn_ra_serf__has_capability(ra_session, &server_supports_depth,
                                      SVN_RA_CAPABILITY_DEPTH, scratch_pool));
  /* We can skip the depth filtering when the user requested
     depth_files or depth_infinity because the server will
     transmit the right stuff anyway. */
  if ((depth != svn_depth_files)
      && (depth != svn_depth_infinity)
      && ! server_supports_depth)
    {
      SVN_ERR(svn_delta_depth_filter_editor(&filter_editor,
                                            &filter_baton,
                                            update_editor,
                                            update_baton,
                                            depth, has_target,
                                            result_pool));
      update_editor = filter_editor;
      update_baton = filter_baton;
    }

  report = apr_pcalloc(result_pool, sizeof(*report));
  report->pool = result_pool;
  report->sess = sess;
  report->target_rev = revision;
  report->ignore_ancestry = ignore_ancestry;
  report->send_copyfrom_args = send_copyfrom_args;
  report->text_deltas = text_deltas;
  report->switched_paths = apr_hash_make(report->pool);

  report->source = src_path;
  report->destination = dest_path;
  report->update_target = update_target;

  report->editor = update_editor;
  report->editor_baton = update_baton;
  report->done = FALSE;

  *reporter = &ra_serf_reporter;
  *report_baton = report;

  report->body =
    svn_ra_serf__request_body_create(SVN_RA_SERF__REQUEST_BODY_IN_MEM_SIZE,
                                     report->pool);
  report->body_template = svn_ra_serf__request_body_get_stream(report->body);

  if (sess->bulk_updates == svn_tristate_true)
    {
      /* User would like to use bulk updates. */
      use_bulk_updates = TRUE;
    }
  else if (sess->bulk_updates == svn_tristate_false)
    {
      /* User doesn't want bulk updates. */
      use_bulk_updates = FALSE;
    }
  else
    {
      /* User doesn't have any preferences on bulk updates. Decide on server
         preferences and capabilities. */
      if (sess->server_allows_bulk)
        {
          if (apr_strnatcasecmp(sess->server_allows_bulk, "off") == 0)
            {
              /* Server doesn't want bulk updates */
              use_bulk_updates = FALSE;
            }
          else if (apr_strnatcasecmp(sess->server_allows_bulk, "prefer") == 0)
            {
              /* Server prefers bulk updates, and we respect that */
              use_bulk_updates = TRUE;
            }
          else
            {
              /* Server allows bulk updates, but doesn't dictate its use. Do
                 whatever is the default. */
              use_bulk_updates = FALSE;
            }
        }
      else
        {
          /* Pre-1.8 server didn't send the bulk_updates header. Check if server
             supports inlining properties in update editor report. */
          if (sess->supports_inline_props)
            {
              /* NOTE: both inlined properties and server->allows_bulk_update
                 (flag SVN_DAV_ALLOW_BULK_UPDATES) were added in 1.8.0, so
                 this code is never reached with a released version of
                 mod_dav_svn.

                 Basically by default a 1.8.0 client connecting to a 1.7.x or
                 older server will always use bulk updates. */

              /* Inline props supported: do not use bulk updates. */
              use_bulk_updates = FALSE;
            }
          else
            {
              /* Inline props are not supported: use bulk updates to avoid
               * PROPFINDs for every added node. */
              use_bulk_updates = TRUE;
            }
        }
    }

  if (use_bulk_updates)
    {
      svn_xml_make_open_tag(&buf, scratch_pool, svn_xml_normal,
                            "S:update-report",
                            "xmlns:S", SVN_XML_NAMESPACE, "send-all", "true",
                            SVN_VA_NULL);
    }
  else
    {
      svn_xml_make_open_tag(&buf, scratch_pool, svn_xml_normal,
                            "S:update-report",
                            "xmlns:S", SVN_XML_NAMESPACE,
                            SVN_VA_NULL);
      /* Subversion 1.8+ servers can be told to send properties for newly
         added items inline even when doing a skelta response. */
      make_simple_xml_tag(&buf, "S:include-props", "yes", scratch_pool);
    }

  make_simple_xml_tag(&buf, "S:src-path", report->source, scratch_pool);

  if (SVN_IS_VALID_REVNUM(report->target_rev))
    {
      make_simple_xml_tag(&buf, "S:target-revision",
                          apr_ltoa(scratch_pool, report->target_rev),
                          scratch_pool);
    }

  if (report->destination && *report->destination)
    {
      make_simple_xml_tag(&buf, "S:dst-path", report->destination,
                          scratch_pool);
    }

  if (report->update_target && *report->update_target)
    {
      make_simple_xml_tag(&buf, "S:update-target", report->update_target,
                          scratch_pool);
    }

  if (report->ignore_ancestry)
    {
      make_simple_xml_tag(&buf, "S:ignore-ancestry", "yes", scratch_pool);
    }

  if (report->send_copyfrom_args)
    {
      make_simple_xml_tag(&buf, "S:send-copyfrom-args", "yes", scratch_pool);
    }

  /* Old servers know "recursive" but not "depth"; help them DTRT. */
  if (depth == svn_depth_files || depth == svn_depth_empty)
    {
      make_simple_xml_tag(&buf, "S:recursive", "no", scratch_pool);
    }

  /* When in 'send-all' mode, mod_dav_svn will assume that it should
     calculate and transmit real text-deltas (instead of empty windows
     that merely indicate "text is changed") unless it finds this
     element.

     NOTE: Do NOT count on servers actually obeying this, as some exist
     which obey send-all, but do not check for this directive at all!

     NOTE 2: When not in 'send-all' mode, mod_dav_svn can still be configured to
     override our request and send text-deltas. */
  if (! text_deltas)
    {
      make_simple_xml_tag(&buf, "S:text-deltas", "no", scratch_pool);
    }

  make_simple_xml_tag(&buf, "S:depth", svn_depth_to_word(depth), scratch_pool);

  SVN_ERR(svn_stream_write(report->body_template, buf->data, &buf->len));

  return SVN_NO_ERROR;
}