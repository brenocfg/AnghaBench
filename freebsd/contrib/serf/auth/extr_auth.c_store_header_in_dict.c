#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  hdrs; int /*<<< orphan*/  header; } ;
typedef  TYPE_1__ auth_baton_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_HASH_KEY_STRING ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 char* apr_pstrmemdup (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ apr_tolower (char) ; 
 scalar_t__ strcasecmp (char const*,int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int store_header_in_dict(void *baton,
                                const char *key,
                                const char *header)
{
    auth_baton_t *ab = baton;
    const char *auth_attr;
    char *auth_name, *c;

    /* We're only interested in xxxx-Authenticate headers. */
    if (strcasecmp(key, ab->header) != 0)
        return 0;

    /* Extract the authentication scheme name.  */
    auth_attr = strchr(header, ' ');
    if (auth_attr) {
        auth_name = apr_pstrmemdup(ab->pool, header, auth_attr - header);
    }
    else
        auth_name = apr_pstrmemdup(ab->pool, header, strlen(header));

    /* Convert scheme name to lower case to enable case insensitive matching. */
    for (c = auth_name; *c != '\0'; c++)
        *c = (char)apr_tolower(*c);

    apr_hash_set(ab->hdrs, auth_name, APR_HASH_KEY_STRING,
                 apr_pstrdup(ab->pool, header));

    return 0;
}