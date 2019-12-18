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
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  ensure_appname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_opt_print_help4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_print_modules (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stringbuf_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
version(const char *progname,
        svn_boolean_t quiet,
        apr_pool_t *pool)
{
  svn_stringbuf_t *version_footer =
    svn_stringbuf_create(_("The following repository access (RA) modules "
                           "are available:\n\n"),
                         pool);

  SVN_ERR(svn_ra_print_modules(version_footer, pool));
  return svn_opt_print_help4(NULL, ensure_appname(progname, pool),
                             TRUE, quiet, FALSE, version_footer->data,
                             NULL, NULL, NULL, NULL, NULL, pool);
}