#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* ecx; } ;
struct TYPE_11__ {TYPE_3__ pkey; TYPE_1__* ameth; } ;
struct TYPE_9__ {int /*<<< orphan*/  pubkey; } ;
struct TYPE_8__ {int /*<<< orphan*/  pkey_id; } ;
typedef  TYPE_4__ EVP_PKEY ;

/* Variables and functions */
#define  ASN1_PKEY_CTRL_GET1_TLS_ENCPT 129 
#define  ASN1_PKEY_CTRL_SET1_TLS_ENCPT 128 
 int KEYLEN (TYPE_4__*) ; 
 int /*<<< orphan*/  KEY_OP_PUBLIC ; 
 unsigned char* OPENSSL_memdup (int /*<<< orphan*/ ,int) ; 
 int ecx_key_op (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ecx_ctrl(EVP_PKEY *pkey, int op, long arg1, void *arg2)
{
    switch (op) {

    case ASN1_PKEY_CTRL_SET1_TLS_ENCPT:
        return ecx_key_op(pkey, pkey->ameth->pkey_id, NULL, arg2, arg1,
                          KEY_OP_PUBLIC);

    case ASN1_PKEY_CTRL_GET1_TLS_ENCPT:
        if (pkey->pkey.ecx != NULL) {
            unsigned char **ppt = arg2;

            *ppt = OPENSSL_memdup(pkey->pkey.ecx->pubkey, KEYLEN(pkey));
            if (*ppt != NULL)
                return KEYLEN(pkey);
        }
        return 0;

    default:
        return -2;

    }
}