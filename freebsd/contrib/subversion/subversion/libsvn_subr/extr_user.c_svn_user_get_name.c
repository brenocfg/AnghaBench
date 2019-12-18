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
 char* get_os_username (int /*<<< orphan*/ *) ; 
 char const* utf8_or_nothing (char const*,int /*<<< orphan*/ *) ; 

const char *
svn_user_get_name(apr_pool_t *pool)
{
  const char *username = get_os_username(pool);
  return utf8_or_nothing(username, pool);
}