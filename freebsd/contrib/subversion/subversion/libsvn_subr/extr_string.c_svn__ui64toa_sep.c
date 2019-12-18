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
typedef  int /*<<< orphan*/  apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int SVN_INT64_BUFFER_SIZE ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ui64toa_sep (int /*<<< orphan*/ ,char,char*) ; 

char *
svn__ui64toa_sep(apr_uint64_t number, char separator, apr_pool_t *pool)
{
  char buffer[2 * SVN_INT64_BUFFER_SIZE];
  ui64toa_sep(number, separator, buffer);

  return apr_pstrdup(pool, buffer);
}