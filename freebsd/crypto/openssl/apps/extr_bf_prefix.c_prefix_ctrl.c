#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * prefix; } ;
typedef  TYPE_1__ PREFIX_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 long BIO_ctrl (int /*<<< orphan*/ *,int,long,void*) ; 
 TYPE_1__* BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_strdup (char const*) ; 
#define  PREFIX_CTRL_SET_PREFIX 128 

__attribute__((used)) static long prefix_ctrl(BIO *b, int cmd, long num, void *ptr)
{
    long ret = 0;

    switch (cmd) {
    case PREFIX_CTRL_SET_PREFIX:
        {
            PREFIX_CTX *ctx = BIO_get_data(b);

            if (ctx == NULL)
                break;

            OPENSSL_free(ctx->prefix);
            ctx->prefix = OPENSSL_strdup((const char *)ptr);
            ret = ctx->prefix != NULL;
        }
        break;
    default:
        if (BIO_next(b) != NULL)
            ret = BIO_ctrl(BIO_next(b), cmd, num, ptr);
        break;
    }
    return ret;
}