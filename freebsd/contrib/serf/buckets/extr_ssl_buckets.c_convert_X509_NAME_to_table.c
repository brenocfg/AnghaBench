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
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  X509_NAME ;

/* Variables and functions */
 int /*<<< orphan*/  APR_HASH_KEY_STRING ; 
 int /*<<< orphan*/  NID_commonName ; 
 int /*<<< orphan*/  NID_countryName ; 
 int /*<<< orphan*/  NID_localityName ; 
 int /*<<< orphan*/  NID_organizationName ; 
 int /*<<< orphan*/  NID_organizationalUnitName ; 
 int /*<<< orphan*/  NID_pkcs9_emailAddress ; 
 int /*<<< orphan*/  NID_stateOrProvinceName ; 
 int X509_NAME_get_text_by_NID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pstrdup_escape_nul_bytes (char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static apr_hash_t *
convert_X509_NAME_to_table(X509_NAME *org, apr_pool_t *pool)
{
    char buf[1024];
    int ret;

    apr_hash_t *tgt = apr_hash_make(pool);

    ret = X509_NAME_get_text_by_NID(org,
                                    NID_commonName,
                                    buf, 1024);
    if (ret != -1)
        apr_hash_set(tgt, "CN", APR_HASH_KEY_STRING,
                     pstrdup_escape_nul_bytes(buf, ret, pool));
    ret = X509_NAME_get_text_by_NID(org,
                                    NID_pkcs9_emailAddress,
                                    buf, 1024);
    if (ret != -1)
        apr_hash_set(tgt, "E", APR_HASH_KEY_STRING,
                     pstrdup_escape_nul_bytes(buf, ret, pool));
    ret = X509_NAME_get_text_by_NID(org,
                                    NID_organizationalUnitName,
                                    buf, 1024);
    if (ret != -1)
        apr_hash_set(tgt, "OU", APR_HASH_KEY_STRING,
                     pstrdup_escape_nul_bytes(buf, ret, pool));
    ret = X509_NAME_get_text_by_NID(org,
                                    NID_organizationName,
                                    buf, 1024);
    if (ret != -1)
        apr_hash_set(tgt, "O", APR_HASH_KEY_STRING,
                     pstrdup_escape_nul_bytes(buf, ret, pool));
    ret = X509_NAME_get_text_by_NID(org,
                                    NID_localityName,
                                    buf, 1024);
    if (ret != -1)
        apr_hash_set(tgt, "L", APR_HASH_KEY_STRING,
                     pstrdup_escape_nul_bytes(buf, ret, pool));
    ret = X509_NAME_get_text_by_NID(org,
                                    NID_stateOrProvinceName,
                                    buf, 1024);
    if (ret != -1)
        apr_hash_set(tgt, "ST", APR_HASH_KEY_STRING,
                     pstrdup_escape_nul_bytes(buf, ret, pool));
    ret = X509_NAME_get_text_by_NID(org,
                                    NID_countryName,
                                    buf, 1024);
    if (ret != -1)
        apr_hash_set(tgt, "C", APR_HASH_KEY_STRING,
                     pstrdup_escape_nul_bytes(buf, ret, pool));

    return tgt;
}