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
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_utf_cstring_to_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
utf8_or_nothing(const char *str, apr_pool_t *pool) {
  if (str)
    {
      const char *utf8_str;
      svn_error_t *err = svn_utf_cstring_to_utf8(&utf8_str, str, pool);
      if (! err)
        return utf8_str;
      svn_error_clear(err);
    }
  return NULL;
}