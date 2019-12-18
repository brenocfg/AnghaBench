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
 char const* SVN_APR_LOCALE_CHARSET ; 
 char const* apr_pstrdup (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ output_encoding ; 

const char *svn_cmdline_output_encoding(apr_pool_t *pool)
{
#ifdef CMDLINE_USE_CUSTOM_ENCODING
  if (output_encoding)
    return apr_pstrdup(pool, output_encoding);
#endif

  return SVN_APR_LOCALE_CHARSET;
}