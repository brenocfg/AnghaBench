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
struct TYPE_4__ {int /*<<< orphan*/  apr_err; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cmdline_fprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,char const*,...) ; 
 int /*<<< orphan*/  svn_err_best_message (TYPE_1__ const*,char*,int) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 
 char* svn_error_symbolic_name (int /*<<< orphan*/ ) ; 

void
svn_handle_warning2(FILE *stream, const svn_error_t *err, const char *prefix)
{
  char buf[256];
#ifdef SVN_DEBUG
  const char *symbolic_name = svn_error_symbolic_name(err->apr_err);
#endif

#ifdef SVN_DEBUG
  if (symbolic_name)
    svn_error_clear(
      svn_cmdline_fprintf(stream, err->pool, "%swarning: apr_err=%s\n",
                          prefix, symbolic_name));
#endif

  svn_error_clear(svn_cmdline_fprintf
                  (stream, err->pool,
                   _("%swarning: W%06d: %s\n"),
                   prefix, err->apr_err,
                   svn_err_best_message(err, buf, sizeof(buf))));
  fflush(stream);
}