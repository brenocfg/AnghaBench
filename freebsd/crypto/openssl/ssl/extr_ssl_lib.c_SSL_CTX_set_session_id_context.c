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
struct TYPE_3__ {unsigned int sid_ctx_length; int /*<<< orphan*/  sid_ctx; } ;
typedef  TYPE_1__ SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_F_SSL_CTX_SET_SESSION_ID_CONTEXT ; 
 unsigned int SSL_MAX_SID_CTX_LENGTH ; 
 int /*<<< orphan*/  SSL_R_SSL_SESSION_ID_CONTEXT_TOO_LONG ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,unsigned int) ; 

int SSL_CTX_set_session_id_context(SSL_CTX *ctx, const unsigned char *sid_ctx,
                                   unsigned int sid_ctx_len)
{
    if (sid_ctx_len > SSL_MAX_SID_CTX_LENGTH) {
        SSLerr(SSL_F_SSL_CTX_SET_SESSION_ID_CONTEXT,
               SSL_R_SSL_SESSION_ID_CONTEXT_TOO_LONG);
        return 0;
    }
    ctx->sid_ctx_length = sid_ctx_len;
    memcpy(ctx->sid_ctx, sid_ctx, sid_ctx_len);

    return 1;
}