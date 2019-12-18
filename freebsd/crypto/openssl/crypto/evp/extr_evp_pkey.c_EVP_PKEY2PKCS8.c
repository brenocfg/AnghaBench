#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* ameth; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* priv_encode ) (int /*<<< orphan*/ *,TYPE_2__*) ;} ;
typedef  int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO ;
typedef  TYPE_2__ EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_F_EVP_PKEY2PKCS8 ; 
 int /*<<< orphan*/  EVP_R_METHOD_NOT_SUPPORTED ; 
 int /*<<< orphan*/  EVP_R_PRIVATE_KEY_ENCODE_ERROR ; 
 int /*<<< orphan*/  EVP_R_UNSUPPORTED_PRIVATE_KEY_ALGORITHM ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PKCS8_PRIV_KEY_INFO_new () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_2__*) ; 

PKCS8_PRIV_KEY_INFO *EVP_PKEY2PKCS8(EVP_PKEY *pkey)
{
    PKCS8_PRIV_KEY_INFO *p8 = PKCS8_PRIV_KEY_INFO_new();
    if (p8  == NULL) {
        EVPerr(EVP_F_EVP_PKEY2PKCS8, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    if (pkey->ameth) {
        if (pkey->ameth->priv_encode) {
            if (!pkey->ameth->priv_encode(p8, pkey)) {
                EVPerr(EVP_F_EVP_PKEY2PKCS8, EVP_R_PRIVATE_KEY_ENCODE_ERROR);
                goto error;
            }
        } else {
            EVPerr(EVP_F_EVP_PKEY2PKCS8, EVP_R_METHOD_NOT_SUPPORTED);
            goto error;
        }
    } else {
        EVPerr(EVP_F_EVP_PKEY2PKCS8, EVP_R_UNSUPPORTED_PRIVATE_KEY_ALGORITHM);
        goto error;
    }
    return p8;
 error:
    PKCS8_PRIV_KEY_INFO_free(p8);
    return NULL;
}