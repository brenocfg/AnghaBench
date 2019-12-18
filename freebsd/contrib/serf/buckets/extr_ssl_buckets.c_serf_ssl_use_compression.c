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
struct TYPE_3__ {int /*<<< orphan*/  ssl; } ;
typedef  TYPE_1__ serf_ssl_context_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EGENERAL ; 
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  SSL_OP_NO_COMPRESSION ; 
 int /*<<< orphan*/  SSL_clear_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

apr_status_t serf_ssl_use_compression(serf_ssl_context_t *ssl_ctx, int enabled)
{
    if (enabled) {
#ifdef SSL_OP_NO_COMPRESSION
        SSL_clear_options(ssl_ctx->ssl, SSL_OP_NO_COMPRESSION);
        return APR_SUCCESS;
#endif
    } else {
#ifdef SSL_OP_NO_COMPRESSION
        SSL_set_options(ssl_ctx->ssl, SSL_OP_NO_COMPRESSION);
        return APR_SUCCESS;
#endif
    }

    return APR_EGENERAL;
}