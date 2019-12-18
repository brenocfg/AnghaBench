#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* cert; } ;
struct TYPE_4__ {int /*<<< orphan*/ * psk_identity_hint; } ;
typedef  TYPE_2__ SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_strdup (char const*) ; 
 scalar_t__ PSK_MAX_IDENTITY_LEN ; 
 int /*<<< orphan*/  SSL_F_SSL_CTX_USE_PSK_IDENTITY_HINT ; 
 int /*<<< orphan*/  SSL_R_DATA_LENGTH_TOO_LONG ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 

int SSL_CTX_use_psk_identity_hint(SSL_CTX *ctx, const char *identity_hint)
{
    if (identity_hint != NULL && strlen(identity_hint) > PSK_MAX_IDENTITY_LEN) {
        SSLerr(SSL_F_SSL_CTX_USE_PSK_IDENTITY_HINT, SSL_R_DATA_LENGTH_TOO_LONG);
        return 0;
    }
    OPENSSL_free(ctx->cert->psk_identity_hint);
    if (identity_hint != NULL) {
        ctx->cert->psk_identity_hint = OPENSSL_strdup(identity_hint);
        if (ctx->cert->psk_identity_hint == NULL)
            return 0;
    } else
        ctx->cert->psk_identity_hint = NULL;
    return 1;
}