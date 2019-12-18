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
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_cmdline_printf (int /*<<< orphan*/ *,char*,char const*,char const*) ; 
 char* svn_time_to_human_cstring (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
svn_cl__info_print_time(apr_time_t atime,
                        const char *desc,
                        apr_pool_t *pool)
{
  const char *time_utf8;

  time_utf8 = svn_time_to_human_cstring(atime, pool);
  return svn_cmdline_printf(pool, "%s: %s\n", desc, time_utf8);
}