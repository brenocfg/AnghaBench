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
typedef  int /*<<< orphan*/ * (* svn_txdelta_window_handler_t ) (int /*<<< orphan*/ *,void*) ;
typedef  int /*<<< orphan*/  svn_txdelta_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct context {scalar_t__ text_deltas; TYPE_1__* editor; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* apply_textdelta ) (void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ * (*) (int /*<<< orphan*/ *,void*),void**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ * (*) (int /*<<< orphan*/ *,void*),void**) ; 
 int /*<<< orphan*/ * svn_txdelta_send_txstream (int /*<<< orphan*/ *,int /*<<< orphan*/ * (*) (int /*<<< orphan*/ *,void*),void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
send_text_delta(struct context *c,
                void *file_baton,
                const char *base_checksum,
                svn_txdelta_stream_t *delta_stream,
                apr_pool_t *pool)
{
  svn_txdelta_window_handler_t delta_handler;
  void *delta_handler_baton;

  /* Get a handler that will apply the delta to the file.  */
  SVN_ERR(c->editor->apply_textdelta
          (file_baton, base_checksum, pool,
           &delta_handler, &delta_handler_baton));

  if (c->text_deltas && delta_stream)
    {
      /* Deliver the delta stream to the file.  */
      return svn_txdelta_send_txstream(delta_stream,
                                       delta_handler,
                                       delta_handler_baton,
                                       pool);
    }
  else
    {
      /* The caller doesn't want text delta data.  Just send a single
         NULL window. */
      return delta_handler(NULL, delta_handler_baton);
    }
}