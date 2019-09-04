#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_sess_set_get_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_sess_set_new_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_async_resumption_get ; 
 int /*<<< orphan*/  on_async_resumption_new ; 

void h2o_socket_ssl_async_resumption_setup_ctx(SSL_CTX *ctx)
{
    SSL_CTX_sess_set_get_cb(ctx, on_async_resumption_get);
    SSL_CTX_sess_set_new_cb(ctx, on_async_resumption_new);
    /* if necessary, it is the responsibility of the caller to disable the internal cache */
}