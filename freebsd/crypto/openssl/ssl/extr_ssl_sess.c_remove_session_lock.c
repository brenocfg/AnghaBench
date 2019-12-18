#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  (* remove_session_cb ) (TYPE_2__*,TYPE_1__*) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  sessions; } ;
struct TYPE_14__ {scalar_t__ session_id_length; int not_resumable; } ;
typedef  TYPE_1__ SSL_SESSION ;
typedef  TYPE_2__ SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_SESSION_free (TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_SESSION_list_remove (TYPE_2__*,TYPE_1__*) ; 
 TYPE_1__* lh_SSL_SESSION_delete (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* lh_SSL_SESSION_retrieve (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static int remove_session_lock(SSL_CTX *ctx, SSL_SESSION *c, int lck)
{
    SSL_SESSION *r;
    int ret = 0;

    if ((c != NULL) && (c->session_id_length != 0)) {
        if (lck)
            CRYPTO_THREAD_write_lock(ctx->lock);
        if ((r = lh_SSL_SESSION_retrieve(ctx->sessions, c)) != NULL) {
            ret = 1;
            r = lh_SSL_SESSION_delete(ctx->sessions, r);
            SSL_SESSION_list_remove(ctx, r);
        }
        c->not_resumable = 1;

        if (lck)
            CRYPTO_THREAD_unlock(ctx->lock);

        if (ctx->remove_session_cb != NULL)
            ctx->remove_session_cb(ctx, c);

        if (ret)
            SSL_SESSION_free(r);
    } else
        ret = 0;
    return ret;
}