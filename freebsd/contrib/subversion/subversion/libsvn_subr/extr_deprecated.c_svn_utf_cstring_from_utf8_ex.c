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
 int /*<<< orphan*/ * svn_utf_cstring_from_utf8_ex2 (char const**,char const*,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_utf_cstring_from_utf8_ex(const char **dest,
                             const char *src,
                             const char *topage,
                             const char *convset_key,
                             apr_pool_t *pool)
{
  return svn_utf_cstring_from_utf8_ex2(dest, src, topage, pool);
}