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
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ apr_env_get (char**,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_uid_homepath_get (char**,char const*,int /*<<< orphan*/ *) ; 
 char* get_os_username (int /*<<< orphan*/ *) ; 
 char const* utf8_or_nothing (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
user_get_homedir(apr_pool_t *pool)
{
  const char *username;
  char *homedir;

  if (apr_env_get(&homedir, "HOME", pool) == APR_SUCCESS)
    return utf8_or_nothing(homedir, pool);

  username = get_os_username(pool);
  if (username != NULL &&
      apr_uid_homepath_get(&homedir, username, pool) == APR_SUCCESS)
    return utf8_or_nothing(homedir, pool);

  return NULL;
}