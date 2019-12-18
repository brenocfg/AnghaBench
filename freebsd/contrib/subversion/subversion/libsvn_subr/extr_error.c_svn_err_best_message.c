#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* message; int /*<<< orphan*/  apr_err; struct TYPE_4__* child; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 scalar_t__ svn_error__is_tracing_link (TYPE_1__ const*) ; 
 char const* svn_strerror (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

const char *
svn_err_best_message(const svn_error_t *err, char *buf, apr_size_t bufsize)
{
  /* Skip over any trace records.  */
  while (svn_error__is_tracing_link(err))
    err = err->child;
  if (err->message)
    return err->message;
  else
    return svn_strerror(err->apr_err, buf, bufsize);
}