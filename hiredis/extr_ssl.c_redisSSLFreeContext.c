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
struct TYPE_3__ {int /*<<< orphan*/ * ssl_ctx; int /*<<< orphan*/ * ssl; } ;
typedef  TYPE_1__ redisSSLContext ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void redisSSLFreeContext(void *privdata){
    redisSSLContext *rsc = privdata;

    if (!rsc) return;
    if (rsc->ssl) {
        SSL_free(rsc->ssl);
        rsc->ssl = NULL;
    }
    if (rsc->ssl_ctx) {
        SSL_CTX_free(rsc->ssl_ctx);
        rsc->ssl_ctx = NULL;
    }
    free(rsc);
}