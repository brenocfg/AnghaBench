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
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr_base64_encode (char*,char const*,scalar_t__) ; 
 scalar_t__ apr_base64_encode_len (scalar_t__) ; 
 int /*<<< orphan*/  apr_cpystrn (char*,char const*,scalar_t__) ; 
 char* apr_palloc (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

void serf__encode_auth_header(const char **header,
                              const char *scheme,
                              const char *data, apr_size_t data_len,
                              apr_pool_t *pool)
{
    apr_size_t encoded_len, scheme_len;
    char *ptr;

    encoded_len = apr_base64_encode_len(data_len);
    scheme_len = strlen(scheme);

    ptr = apr_palloc(pool, encoded_len + scheme_len + 1);
    *header = ptr;

    apr_cpystrn(ptr, scheme, scheme_len + 1);
    ptr += scheme_len;
    *ptr++ = ' ';

    apr_base64_encode(ptr, data, data_len);
}