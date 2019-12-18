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
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int APR_MD5_DIGESTSIZE ; 
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ apr_md5 (unsigned char*,char const*,int /*<<< orphan*/ ) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,char const*,char const*,char const*) ; 
 char* hex_encode (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static apr_status_t
build_digest_ha1(const char **out_ha1,
                 const char *username,
                 const char *password,
                 const char *realm_name,
                 apr_pool_t *pool)
{
    const char *tmp;
    unsigned char ha1[APR_MD5_DIGESTSIZE];
    apr_status_t status;

    /* calculate ha1:
       MD5 hash of the combined user name, authentication realm and password */
    tmp = apr_psprintf(pool, "%s:%s:%s",
                       username,
                       realm_name,
                       password);
    status = apr_md5(ha1, tmp, strlen(tmp));
    if (status)
        return status;

    *out_ha1 = hex_encode(ha1, pool);

    return APR_SUCCESS;
}