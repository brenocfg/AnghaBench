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
typedef  int /*<<< orphan*/  apr_uuid_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ APR_UUID_FORMATTED_LENGTH ; 
 char* apr_pcalloc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  apr_uuid_format (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_uuid_get (int /*<<< orphan*/ *) ; 

const char *
svn_uuid_generate(apr_pool_t *pool)
{
  apr_uuid_t uuid;
  char *uuid_str = apr_pcalloc(pool, APR_UUID_FORMATTED_LENGTH + 1);
  apr_uuid_get(&uuid);
  apr_uuid_format(uuid_str, &uuid);
  return uuid_str;
}