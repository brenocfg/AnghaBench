#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ ptls_encrypt_ticket_t ;
struct TYPE_10__ {int ticket_lifetime; TYPE_3__* encrypt_ticket; } ;
typedef  TYPE_4__ ptls_context_t ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;
struct TYPE_8__ {int /*<<< orphan*/ * update_thread; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* setup ) (int /*<<< orphan*/ **,size_t) ;} ;
struct TYPE_11__ {TYPE_2__ ticket; TYPE_1__ cache; } ;
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int SSL_CTX_get_options (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_options (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_tlsext_ticket_key_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SSL_OP_NO_TICKET ; 
 TYPE_6__ conf ; 
 int /*<<< orphan*/  encrypt_ticket_key_ptls ; 
 int /*<<< orphan*/  h2o_multithread_create_thread (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* h2o_socket_ssl_get_picotls_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **,size_t) ; 
 int /*<<< orphan*/  ticket_key_callback_ossl ; 

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
            ptls_context_t *pctx = h2o_socket_ssl_get_picotls_context(ctx);
            if (pctx != NULL) {
                static ptls_encrypt_ticket_t encryptor = {encrypt_ticket_key_ptls};
                pctx->ticket_lifetime = 86400 * 7; // FIXME conf.lifetime;
                pctx->encrypt_ticket = &encryptor;
            }
        }
    } else {
        size_t i;
        for (i = 0; i != num_contexts; ++i)
            SSL_CTX_set_options(contexts[i], SSL_CTX_get_options(contexts[i]) | SSL_OP_NO_TICKET);
    }
#endif
}