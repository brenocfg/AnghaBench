#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lifetime; } ;
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_SESSID_CTX ; 
 int /*<<< orphan*/  H2O_SESSID_CTX_LEN ; 
 int /*<<< orphan*/  SSL_CTX_set_session_cache_mode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_session_id_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SSL_SESS_CACHE_NO_AUTO_CLEAR ; 
 int SSL_SESS_CACHE_SERVER ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  h2o_socket_ssl_async_resumption_setup_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spawn_cache_cleanup_thread (int /*<<< orphan*/ **,size_t) ; 

__attribute__((used)) static void setup_cache_enable(SSL_CTX **contexts, size_t num_contexts, int async_resumption)
{
    size_t i;
    for (i = 0; i != num_contexts; ++i) {
        SSL_CTX_set_session_cache_mode(contexts[i], SSL_SESS_CACHE_SERVER | SSL_SESS_CACHE_NO_AUTO_CLEAR);
        SSL_CTX_set_session_id_context(contexts[i], H2O_SESSID_CTX, H2O_SESSID_CTX_LEN);
        SSL_CTX_set_timeout(contexts[i], conf.lifetime);
        if (async_resumption)
            h2o_socket_ssl_async_resumption_setup_ctx(contexts[i]);
    }
    spawn_cache_cleanup_thread(contexts, num_contexts);
}