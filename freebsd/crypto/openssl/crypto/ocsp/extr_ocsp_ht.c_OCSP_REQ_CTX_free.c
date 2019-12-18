#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* iobuf; int /*<<< orphan*/  mem; } ;
typedef  TYPE_1__ OCSP_REQ_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

void OCSP_REQ_CTX_free(OCSP_REQ_CTX *rctx)
{
    if (!rctx)
        return;
    BIO_free(rctx->mem);
    OPENSSL_free(rctx->iobuf);
    OPENSSL_free(rctx);
}