#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_7__ {int /*<<< orphan*/  body_template; } ;
typedef  TYPE_2__ report_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 int /*<<< orphan*/  apr_ltoa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_depth_to_word (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_xml_escape_cdata_cstring (TYPE_1__**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_xml_make_close_tag (TYPE_1__**,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_xml_make_open_tag (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,char const*,char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_xml_protect_pcdata ; 

__attribute__((used)) static svn_error_t *
set_path(void *report_baton,
         const char *path,
         svn_revnum_t revision,
         svn_depth_t depth,
         svn_boolean_t start_empty,
         const char *lock_token,
         apr_pool_t *pool)
{
  report_context_t *report = report_baton;
  svn_stringbuf_t *buf = NULL;

  svn_xml_make_open_tag(&buf, pool, svn_xml_protect_pcdata, "S:entry",
                        "rev", apr_ltoa(pool, revision),
                        "lock-token", lock_token,
                        "depth", svn_depth_to_word(depth),
                        "start-empty", start_empty ? "true" : NULL,
                        SVN_VA_NULL);
  svn_xml_escape_cdata_cstring(&buf, path, pool);
  svn_xml_make_close_tag(&buf, pool, "S:entry");

  SVN_ERR(svn_stream_write(report->body_template, buf->data, &buf->len));

  return SVN_NO_ERROR;
}