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
struct TYPE_3__ {int flags; scalar_t__ ssl; scalar_t__ ctx; } ;
typedef  TYPE_1__ SSL_CONF_CTX ;

/* Variables and functions */
 int SSL_CONF_FLAG_CERTIFICATE ; 
 int SSL_CTX_use_PrivateKey_file (scalar_t__,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_FILETYPE_PEM ; 
 int SSL_use_PrivateKey_file (scalar_t__,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmd_PrivateKey(SSL_CONF_CTX *cctx, const char *value)
{
    int rv = 1;
    if (!(cctx->flags & SSL_CONF_FLAG_CERTIFICATE))
        return -2;
    if (cctx->ctx)
        rv = SSL_CTX_use_PrivateKey_file(cctx->ctx, value, SSL_FILETYPE_PEM);
    if (cctx->ssl)
        rv = SSL_use_PrivateKey_file(cctx->ssl, value, SSL_FILETYPE_PEM);
    return rv > 0;
}