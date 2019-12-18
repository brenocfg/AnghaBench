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
 char* apr_palloc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  apr_uuid_format (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_uuid_get (int /*<<< orphan*/ *) ; 
 char const* hex_encode (unsigned char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
random_cnonce(apr_pool_t *pool)
{
    apr_uuid_t uuid;
    char *buf = apr_palloc(pool, APR_UUID_FORMATTED_LENGTH + 1);

    apr_uuid_get(&uuid);
    apr_uuid_format(buf, &uuid);

    return hex_encode((unsigned char*)buf, pool);
}