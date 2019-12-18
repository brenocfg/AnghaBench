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
struct TYPE_6__ {TYPE_1__* digest; } ;
struct TYPE_5__ {int md_size; } ;
typedef  TYPE_2__ EVP_MD_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 TYPE_2__* BIO_get_data (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_DigestFinal_ex (TYPE_2__*,unsigned char*,unsigned int*) ; 

__attribute__((used)) static int md_gets(BIO *bp, char *buf, int size)
{
    EVP_MD_CTX *ctx;
    unsigned int ret;

    ctx = BIO_get_data(bp);

    if (size < ctx->digest->md_size)
        return 0;

    if (EVP_DigestFinal_ex(ctx, (unsigned char *)buf, &ret) <= 0)
        return -1;

    return (int)ret;
}