#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* priv; } ;
typedef  TYPE_1__ svn_ra_session_t ;
struct TYPE_5__ {int /*<<< orphan*/ * shim_callbacks; } ;
typedef  TYPE_2__ svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_delta_shim_callbacks_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 

svn_error_t *
svn_ra_serf__register_editor_shim_callbacks(svn_ra_session_t *ra_session,
                                    svn_delta_shim_callbacks_t *callbacks)
{
  svn_ra_serf__session_t *session = ra_session->priv;

  session->shim_callbacks = callbacks;
  return SVN_NO_ERROR;
}