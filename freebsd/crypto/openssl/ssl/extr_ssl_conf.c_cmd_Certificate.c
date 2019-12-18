#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* cert; } ;
struct TYPE_8__ {TYPE_2__* cert; } ;
struct TYPE_7__ {size_t key; size_t pkeys; } ;
struct TYPE_6__ {int flags; char** cert_filename; TYPE_4__* ssl; TYPE_5__* ctx; } ;
typedef  TYPE_1__ SSL_CONF_CTX ;
typedef  TYPE_2__ CERT ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_strdup (char const*) ; 
 int SSL_CONF_FLAG_REQUIRE_PRIVATE ; 
 int SSL_CTX_use_certificate_chain_file (TYPE_5__*,char const*) ; 
 int SSL_use_certificate_chain_file (TYPE_4__*,char const*) ; 

__attribute__((used)) static int cmd_Certificate(SSL_CONF_CTX *cctx, const char *value)
{
    int rv = 1;
    CERT *c = NULL;
    if (cctx->ctx) {
        rv = SSL_CTX_use_certificate_chain_file(cctx->ctx, value);
        c = cctx->ctx->cert;
    }
    if (cctx->ssl) {
        rv = SSL_use_certificate_chain_file(cctx->ssl, value);
        c = cctx->ssl->cert;
    }
    if (rv > 0 && c && cctx->flags & SSL_CONF_FLAG_REQUIRE_PRIVATE) {
        char **pfilename = &cctx->cert_filename[c->key - c->pkeys];
        OPENSSL_free(*pfilename);
        *pfilename = OPENSSL_strdup(value);
        if (!*pfilename)
            rv = 0;
    }

    return rv > 0;
}