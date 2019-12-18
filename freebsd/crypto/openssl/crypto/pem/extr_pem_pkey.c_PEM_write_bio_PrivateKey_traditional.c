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
typedef  int /*<<< orphan*/  pem_password_cb ;
typedef  int /*<<< orphan*/  i2d_of_void ;
struct TYPE_6__ {TYPE_1__* ameth; } ;
struct TYPE_5__ {int /*<<< orphan*/  pem_str; } ;
typedef  TYPE_2__ EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int PEM_ASN1_write_bio (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/  const*,unsigned char*,int,int /*<<< orphan*/ *,void*) ; 
 scalar_t__ i2d_PrivateKey ; 

int PEM_write_bio_PrivateKey_traditional(BIO *bp, EVP_PKEY *x,
                                         const EVP_CIPHER *enc,
                                         unsigned char *kstr, int klen,
                                         pem_password_cb *cb, void *u)
{
    char pem_str[80];
    BIO_snprintf(pem_str, 80, "%s PRIVATE KEY", x->ameth->pem_str);
    return PEM_ASN1_write_bio((i2d_of_void *)i2d_PrivateKey,
                              pem_str, bp, x, enc, kstr, klen, cb, u);
}