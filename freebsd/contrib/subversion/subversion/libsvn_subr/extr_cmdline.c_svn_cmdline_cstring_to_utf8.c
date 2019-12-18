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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * input_encoding ; 
 int /*<<< orphan*/ * svn_utf_cstring_to_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_utf_cstring_to_utf8_ex2 (char const**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_cmdline_cstring_to_utf8(const char **dest,
                            const char *src,
                            apr_pool_t *pool)
{
#ifdef CMDLINE_USE_CUSTOM_ENCODING
  if (input_encoding != NULL)
    return svn_utf_cstring_to_utf8_ex2(dest, src, input_encoding, pool);
#endif

  return svn_utf_cstring_to_utf8(dest, src, pool);
}