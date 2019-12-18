#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* pkey; int /*<<< orphan*/ * data; int /*<<< orphan*/ * engine; } ;
struct TYPE_5__ {scalar_t__ ptr; } ;
struct TYPE_6__ {TYPE_1__ pkey; } ;
typedef  TYPE_3__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  CMAC_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CMAC_CTX_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CMAC_Init (int /*<<< orphan*/ *,void*,int,void*,int /*<<< orphan*/ *) ; 
#define  EVP_PKEY_CTRL_CIPHER 130 
#define  EVP_PKEY_CTRL_MD 129 
#define  EVP_PKEY_CTRL_SET_MAC_KEY 128 

__attribute__((used)) static int pkey_cmac_ctrl(EVP_PKEY_CTX *ctx, int type, int p1, void *p2)
{
    CMAC_CTX *cmctx = ctx->data;
    switch (type) {

    case EVP_PKEY_CTRL_SET_MAC_KEY:
        if (!p2 || p1 < 0)
            return 0;
        if (!CMAC_Init(cmctx, p2, p1, NULL, NULL))
            return 0;
        break;

    case EVP_PKEY_CTRL_CIPHER:
        if (!CMAC_Init(cmctx, NULL, 0, p2, ctx->engine))
            return 0;
        break;

    case EVP_PKEY_CTRL_MD:
        if (ctx->pkey && !CMAC_CTX_copy(ctx->data,
                                        (CMAC_CTX *)ctx->pkey->pkey.ptr))
            return 0;
        if (!CMAC_Init(cmctx, NULL, 0, NULL, NULL))
            return 0;
        break;

    default:
        return -2;

    }
    return 1;
}