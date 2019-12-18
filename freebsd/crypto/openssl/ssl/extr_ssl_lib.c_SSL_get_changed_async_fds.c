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
struct TYPE_3__ {int /*<<< orphan*/ * waitctx; } ;
typedef  TYPE_1__ SSL ;
typedef  int /*<<< orphan*/  OSSL_ASYNC_FD ;
typedef  int /*<<< orphan*/  ASYNC_WAIT_CTX ;

/* Variables and functions */
 int ASYNC_WAIT_CTX_get_changed_fds (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,size_t*) ; 

int SSL_get_changed_async_fds(SSL *s, OSSL_ASYNC_FD *addfd, size_t *numaddfds,
                              OSSL_ASYNC_FD *delfd, size_t *numdelfds)
{
    ASYNC_WAIT_CTX *ctx = s->waitctx;

    if (ctx == NULL)
        return 0;
    return ASYNC_WAIT_CTX_get_changed_fds(ctx, addfd, numaddfds, delfd,
                                          numdelfds);
}