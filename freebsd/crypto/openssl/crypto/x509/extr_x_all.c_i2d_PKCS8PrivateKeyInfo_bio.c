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
typedef  int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_PKEY2PKCS8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO_free (int /*<<< orphan*/ *) ; 
 int i2d_PKCS8_PRIV_KEY_INFO_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int i2d_PKCS8PrivateKeyInfo_bio(BIO *bp, EVP_PKEY *key)
{
    PKCS8_PRIV_KEY_INFO *p8inf;
    int ret;
    p8inf = EVP_PKEY2PKCS8(key);
    if (!p8inf)
        return 0;
    ret = i2d_PKCS8_PRIV_KEY_INFO_bio(bp, p8inf);
    PKCS8_PRIV_KEY_INFO_free(p8inf);
    return ret;
}