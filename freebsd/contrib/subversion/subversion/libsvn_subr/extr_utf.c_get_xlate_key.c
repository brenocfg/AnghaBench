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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char const* SVN_APR_DEFAULT_CHARSET ; 
 char const* SVN_APR_LOCALE_CHARSET ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 char const* apr_pstrcat (int /*<<< orphan*/ *,char*,char const*,char*,char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char*
get_xlate_key(const char *topage,
              const char *frompage,
              apr_pool_t *pool)
{
  /* In the cases of SVN_APR_LOCALE_CHARSET and SVN_APR_DEFAULT_CHARSET
   * topage/frompage is really an int, not a valid string.  So generate a
   * unique key accordingly. */
  if (frompage == SVN_APR_LOCALE_CHARSET)
    frompage = "APR_LOCALE_CHARSET";
  else if (frompage == SVN_APR_DEFAULT_CHARSET)
    frompage = "APR_DEFAULT_CHARSET";

  if (topage == SVN_APR_LOCALE_CHARSET)
    topage = "APR_LOCALE_CHARSET";
  else if (topage == SVN_APR_DEFAULT_CHARSET)
    topage = "APR_DEFAULT_CHARSET";

  return apr_pstrcat(pool, "svn-utf-", frompage, "to", topage,
                     "-xlate-handle", SVN_VA_NULL);
}