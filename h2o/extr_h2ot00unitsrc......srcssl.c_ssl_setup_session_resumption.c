#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* setup ) (int /*<<< orphan*/ **,size_t) ;} ;
struct TYPE_4__ {TYPE_1__ cache; } ;
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 TYPE_2__ conf ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **,size_t) ; 

void ssl_setup_session_resumption(SSL_CTX **contexts, size_t num_contexts)
{
    if (conf.cache.setup != NULL)
        conf.cache.setup(contexts, num_contexts);

#if H2O_USE_SESSION_TICKETS
    if (num_contexts == 0)
        return;

    if (conf.ticket.update_thread != NULL) {
        /* start session ticket updater thread */
        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, 1);
        h2o_multithread_create_thread(&tid, &attr, conf.ticket.update_thread, NULL);
        size_t i;
        for (i = 0; i != num_contexts; ++i) {
            SSL_CTX *ctx = contexts[i];
            SSL_CTX_set_tlsext_ticket_key_cb(ctx, ticket_key_callback_ossl);
#if H2O_USE_PICOTLS
            ptls_context_t *pctx = h2o_socket_ssl_get_picotls_context(ctx);
            if (pctx != NULL) {
                static ptls_encrypt_ticket_t encryptor = {encrypt_ticket_key_ptls};
                pctx->ticket_lifetime = 86400 * 7; // FIXME conf.lifetime;
                pctx->encrypt_ticket = &encryptor;
            }
#endif
        }
    } else {
        size_t i;
        for (i = 0; i != num_contexts; ++i)
            SSL_CTX_set_options(contexts[i], SSL_CTX_get_options(contexts[i]) | SSL_OP_NO_TICKET);
    }
#endif
}