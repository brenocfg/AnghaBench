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
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get1_EC_KEY (int /*<<< orphan*/ *) ; 

__attribute__((used)) static EC_KEY *pkey_get_eckey(EVP_PKEY *key, EC_KEY **eckey)
{
    EC_KEY *dtmp;
    if (!key)
        return NULL;
    dtmp = EVP_PKEY_get1_EC_KEY(key);
    EVP_PKEY_free(key);
    if (!dtmp)
        return NULL;
    if (eckey) {
        EC_KEY_free(*eckey);
        *eckey = dtmp;
    }
    return dtmp;
}