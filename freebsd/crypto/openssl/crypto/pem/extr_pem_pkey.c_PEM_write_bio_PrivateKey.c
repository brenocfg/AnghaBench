#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pem_password_cb ;
struct TYPE_7__ {TYPE_1__* ameth; } ;
struct TYPE_6__ {int /*<<< orphan*/ * priv_encode; } ;
typedef  TYPE_2__ EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int PEM_write_bio_PKCS8PrivateKey (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/  const*,char*,int,int /*<<< orphan*/ *,void*) ; 
 int PEM_write_bio_PrivateKey_traditional (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/  const*,unsigned char*,int,int /*<<< orphan*/ *,void*) ; 

int PEM_write_bio_PrivateKey(BIO *bp, EVP_PKEY *x, const EVP_CIPHER *enc,
                             unsigned char *kstr, int klen,
                             pem_password_cb *cb, void *u)
{
    if (x->ameth == NULL || x->ameth->priv_encode != NULL)
        return PEM_write_bio_PKCS8PrivateKey(bp, x, enc,
                                             (char *)kstr, klen, cb, u);
    return PEM_write_bio_PrivateKey_traditional(bp, x, enc, kstr, klen, cb, u);
}