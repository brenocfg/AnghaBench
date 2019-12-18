#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_serf__xml_estate_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct revision_report_t {struct replay_node_t* current_node; } ;
struct replay_node_t {scalar_t__ stream; int /*<<< orphan*/  file; } ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int REPLAY_APPLY_TEXTDELTA ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_STREAM_UNEXPECTED_EOF ; 
 int /*<<< orphan*/  SVN_ERR_XML_MALFORMED ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * _ (char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_write (scalar_t__,char const*,scalar_t__*) ; 

__attribute__((used)) static svn_error_t *
replay_cdata(svn_ra_serf__xml_estate_t *xes,
             void *baton,
             int current_state,
             const char *data,
             apr_size_t len,
             apr_pool_t *scratch_pool)
{
  struct revision_report_t *ctx = baton;

  if (current_state == REPLAY_APPLY_TEXTDELTA)
    {
      struct replay_node_t *node = ctx->current_node;

      if (! node || ! node->file)
        return svn_error_create(SVN_ERR_XML_MALFORMED, NULL, NULL);

      if (node->stream)
        {
          apr_size_t written = len;

          SVN_ERR(svn_stream_write(node->stream, data, &written));
          if (written != len)
            return svn_error_create(SVN_ERR_STREAM_UNEXPECTED_EOF, NULL,
                                    _("Error writing stream: unexpected EOF"));
        }
    }

  return SVN_NO_ERROR;
}