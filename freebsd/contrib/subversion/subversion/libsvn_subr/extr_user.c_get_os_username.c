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
typedef  int /*<<< orphan*/  apr_uid_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_gid_t ;

/* Variables and functions */
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ apr_uid_current (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_uid_name_get (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
get_os_username(apr_pool_t *pool)
{
#if APR_HAS_USER
  char *username;
  apr_uid_t uid;
  apr_gid_t gid;

  if (apr_uid_current(&uid, &gid, pool) == APR_SUCCESS &&
      apr_uid_name_get(&username, uid, pool) == APR_SUCCESS)
    return username;
#endif

  return NULL;
}