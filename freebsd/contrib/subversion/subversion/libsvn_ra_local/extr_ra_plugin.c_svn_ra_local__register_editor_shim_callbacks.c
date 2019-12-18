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
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_delta_shim_callbacks_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 

__attribute__((used)) static svn_error_t *
svn_ra_local__register_editor_shim_callbacks(svn_ra_session_t *session,
                                    svn_delta_shim_callbacks_t *callbacks)
{
  /* This is currenly a no-op, since we don't provide our own editor, just
     use the one the libsvn_repos hands back to us. */
  return SVN_NO_ERROR;
}