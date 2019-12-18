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
typedef  int /*<<< orphan*/  svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 char* apr_pstrcat (int /*<<< orphan*/ *,char const*,char*,char const*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opt_revision_to_string (char const**,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__serialize_file_external(const char **str,
                                const char *path,
                                const svn_opt_revision_t *peg_rev,
                                const svn_opt_revision_t *rev,
                                apr_pool_t *pool)
{
  const char *s;

  if (path)
    {
      const char *s1;
      const char *s2;

      SVN_ERR(opt_revision_to_string(&s1, path, peg_rev, pool));
      SVN_ERR(opt_revision_to_string(&s2, path, rev, pool));

      s = apr_pstrcat(pool, s1, ":", s2, ":", path, SVN_VA_NULL);
    }
  else
    s = NULL;

  *str = s;

  return SVN_NO_ERROR;
}