#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  message; int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_1__ svn_error_t ;

/* Variables and functions */
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  error_tracing_link ; 
 TYPE_1__* make_error_internal (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  svn_error__locate (char const*,long) ; 

svn_error_t *
svn_error__trace(const char *file, long line, svn_error_t *err)
{
#ifndef SVN_DEBUG

  /* We shouldn't even be here, but whatever. Just return the error as-is.  */
  return err;

#else

  /* Only do the work when an error occurs.  */
  if (err)
    {
      svn_error_t *trace;
      svn_error__locate(file, line);
      trace = make_error_internal(err->apr_err, err);
      trace->message = error_tracing_link;
      return trace;
    }
  return SVN_NO_ERROR;

#endif
}