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
struct TYPE_3__ {int /*<<< orphan*/  ctx; scalar_t__ ssl; } ;
typedef  TYPE_1__ SSL_CONF_CTX ;

/* Variables and functions */
 int SSL_CTX_set1_client_sigalgs_list (int /*<<< orphan*/ ,char const*) ; 
 int SSL_set1_client_sigalgs_list (scalar_t__,char const*) ; 

__attribute__((used)) static int cmd_ClientSignatureAlgorithms(SSL_CONF_CTX *cctx, const char *value)
{
    int rv;
    if (cctx->ssl)
        rv = SSL_set1_client_sigalgs_list(cctx->ssl, value);
    /* NB: ctx == NULL performs syntax checking only */
    else
        rv = SSL_CTX_set1_client_sigalgs_list(cctx->ctx, value);
    return rv > 0;
}