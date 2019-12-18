#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;

/* Variables and functions */
 scalar_t__ SVN_ERR_CLIENT_MODIFIED ; 
 scalar_t__ SVN_ERR_UNVERSIONED_RESOURCE ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* svn_error_quick_wrap (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 

svn_error_t *
svn_cl__may_need_force(svn_error_t *err)
{
  if (err
      && (err->apr_err == SVN_ERR_UNVERSIONED_RESOURCE ||
          err->apr_err == SVN_ERR_CLIENT_MODIFIED))
    {
      /* Should this svn_error_compose a new error number? Probably not,
         the error hasn't changed. */
      err = svn_error_quick_wrap
        (err, _("Use --force to override this restriction (local modifications "
         "may be lost)"));
    }

  return svn_error_trace(err);
}