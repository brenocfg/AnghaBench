#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_txdelta_window_handler_t ;
typedef  int /*<<< orphan*/  svn_txdelta_stream_t ;
typedef  int /*<<< orphan*/  (* svn_txdelta_stream_open_func_t ) (int /*<<< orphan*/ **,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* apply_textdelta ) (void*,char const*,int /*<<< orphan*/ *,scalar_t__*,void**) ;} ;
typedef  TYPE_1__ svn_delta_editor_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (void*,char const*,int /*<<< orphan*/ *,scalar_t__*,void**) ; 
 scalar_t__ svn_delta_noop_window_handler ; 
 int /*<<< orphan*/  svn_txdelta_send_txstream (int /*<<< orphan*/ *,scalar_t__,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
apply_textdelta_stream(const svn_delta_editor_t *editor,
                       void *file_baton,
                       const char *base_checksum,
                       svn_txdelta_stream_open_func_t open_func,
                       void *open_baton,
                       apr_pool_t *scratch_pool)
{
  svn_txdelta_window_handler_t handler;
  void *handler_baton;

  SVN_ERR(editor->apply_textdelta(file_baton, base_checksum,
                                  scratch_pool, &handler,
                                  &handler_baton));
  if (handler != svn_delta_noop_window_handler)
    {
      svn_txdelta_stream_t *txdelta_stream;

      SVN_ERR(open_func(&txdelta_stream, open_baton, scratch_pool,
                        scratch_pool));
      SVN_ERR(svn_txdelta_send_txstream(txdelta_stream, handler,
                                        handler_baton, scratch_pool));
    }

  return SVN_NO_ERROR;
}