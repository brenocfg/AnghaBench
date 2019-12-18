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
typedef  int /*<<< orphan*/  serf_socket_remove_t ;
typedef  int /*<<< orphan*/  serf_socket_add_t ;
struct TYPE_4__ {int /*<<< orphan*/  pollset; } ;
typedef  TYPE_1__ serf_pollset_t ;
struct TYPE_5__ {int /*<<< orphan*/  server_authn_info; int /*<<< orphan*/  authn_types; scalar_t__ progress_written; scalar_t__ progress_read; int /*<<< orphan*/  conns; int /*<<< orphan*/  pollset_rm; int /*<<< orphan*/  pollset_add; TYPE_1__* pollset_baton; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_2__ serf_context_t ;
typedef  int /*<<< orphan*/  serf_connection_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_POLLSET_SELECT ; 
 int /*<<< orphan*/  MAX_CONN ; 
 int /*<<< orphan*/  SERF_AUTHN_ALL ; 
 int /*<<< orphan*/  apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pollset_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pollset_create_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pollset_add ; 
 int /*<<< orphan*/  pollset_rm ; 

serf_context_t *serf_context_create_ex(
    void *user_baton,
    serf_socket_add_t addf,
    serf_socket_remove_t rmf,
    apr_pool_t *pool)
{
    serf_context_t *ctx = apr_pcalloc(pool, sizeof(*ctx));

    ctx->pool = pool;

    if (user_baton != NULL) {
        ctx->pollset_baton = user_baton;
        ctx->pollset_add = addf;
        ctx->pollset_rm = rmf;
    }
    else {
        /* build the pollset with a (default) number of connections */
        serf_pollset_t *ps = apr_pcalloc(pool, sizeof(*ps));

        /* ### TODO: As of APR 1.4.x apr_pollset_create_ex can return a status
           ### other than APR_SUCCESS, so we should handle it.
           ### Probably move creation of the pollset to later when we have
           ### the possibility of returning status to the caller.
         */
#ifdef BROKEN_WSAPOLL
        /* APR 1.4.x switched to using WSAPoll() on Win32, but it does not
         * properly handle errors on a non-blocking sockets (such as
         * connecting to a server where no listener is active).
         *
         * So, sadly, we must force using select() on Win32.
         *
         * http://mail-archives.apache.org/mod_mbox/apr-dev/201105.mbox/%3CBANLkTin3rBCecCBRvzUA5B-14u-NWxR_Kg@mail.gmail.com%3E
         */
        (void) apr_pollset_create_ex(&ps->pollset, MAX_CONN, pool, 0,
                                     APR_POLLSET_SELECT);
#else
        (void) apr_pollset_create(&ps->pollset, MAX_CONN, pool, 0);
#endif
        ctx->pollset_baton = ps;
        ctx->pollset_add = pollset_add;
        ctx->pollset_rm = pollset_rm;
    }

    /* default to a single connection since that is the typical case */
    ctx->conns = apr_array_make(pool, 1, sizeof(serf_connection_t *));

    /* Initialize progress status */
    ctx->progress_read = 0;
    ctx->progress_written = 0;

    ctx->authn_types = SERF_AUTHN_ALL;
    ctx->server_authn_info = apr_hash_make(pool);

    return ctx;
}