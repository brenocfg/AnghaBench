#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_txdelta_window_handler_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  wrapped_node_baton; TYPE_3__* edit_baton; } ;
typedef  TYPE_2__ node_baton_t ;
struct TYPE_6__ {TYPE_1__* wrapped_editor; scalar_t__ got_textdeltas; int /*<<< orphan*/  quiet; } ;
typedef  TYPE_3__ edit_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_4__ {int /*<<< orphan*/ * (* apply_textdelta ) (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  svn_cmdline_fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_cmdline_printf (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static svn_error_t *
apply_textdelta(void *file_baton,
                const char *base_checksum,
                apr_pool_t *pool,
                svn_txdelta_window_handler_t *handler,
                void **handler_baton)
{
  node_baton_t *fb = file_baton;
  edit_baton_t *eb = fb->edit_baton;

  if (! eb->quiet)
    {
      if (! eb->got_textdeltas)
        SVN_ERR(svn_cmdline_printf(pool, _("Transmitting file data ")));
      SVN_ERR(svn_cmdline_printf(pool, "."));
      SVN_ERR(svn_cmdline_fflush(stdout));
    }

  eb->got_textdeltas = TRUE;
  return eb->wrapped_editor->apply_textdelta(fb->wrapped_node_baton,
                                             base_checksum, pool,
                                             handler, handler_baton);
}