#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  svn_fs_print_modules (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_opt_print_help4 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_appendcstr (TYPE_1__*,char*) ; 
 TYPE_1__* svn_stringbuf_create (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t * version(svn_boolean_t quiet, apr_pool_t *pool)
{
  const char *fs_desc_start
    = _("The following repository back-end (FS) modules are available:\n\n");

  svn_stringbuf_t *version_footer;

  version_footer = svn_stringbuf_create(fs_desc_start, pool);
  SVN_ERR(svn_fs_print_modules(version_footer, pool));

#ifdef SVN_HAVE_SASL
  svn_stringbuf_appendcstr(version_footer,
                           _("\nCyrus SASL authentication is available.\n"));
#endif

  return svn_opt_print_help4(NULL, "svnserve", TRUE, quiet, FALSE,
                             version_footer->data,
                             NULL, NULL, NULL, NULL, NULL, pool);
}