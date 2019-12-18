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
typedef  int /*<<< orphan*/  svn_txdelta_window_handler_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct file_baton {int /*<<< orphan*/  wrapped_file_baton; struct edit_baton* edit_baton; } ;
struct edit_baton {TYPE_1__* wrapped_editor; int /*<<< orphan*/  out; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* apply_textdelta ) (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  svn_stream_printf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  write_indent (struct edit_baton*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
apply_textdelta(void *file_baton,
                const char *base_checksum,
                apr_pool_t *pool,
                svn_txdelta_window_handler_t *handler,
                void **handler_baton)
{
  struct file_baton *fb = file_baton;
  struct edit_baton *eb = fb->edit_baton;

  SVN_ERR(write_indent(eb, pool));
  SVN_ERR(svn_stream_printf(eb->out, pool, "apply_textdelta : %s\n",
                            base_checksum));

  SVN_ERR(eb->wrapped_editor->apply_textdelta(fb->wrapped_file_baton,
                                              base_checksum,
                                              pool,
                                              handler,
                                              handler_baton));

  return SVN_NO_ERROR;
}