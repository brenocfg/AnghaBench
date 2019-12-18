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
struct TYPE_4__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  server_authn_info; } ;
typedef  TYPE_1__ serf_context_t ;
struct TYPE_5__ {int /*<<< orphan*/  host_url; TYPE_1__* ctx; } ;
typedef  TYPE_2__ serf_connection_t ;
typedef  int /*<<< orphan*/  serf__authn_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_HASH_KEY_STRING ; 
 int /*<<< orphan*/ * apr_hash_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

serf__authn_info_t *serf__get_authn_info_for_server(serf_connection_t *conn)
{
    serf_context_t *ctx = conn->ctx;
    serf__authn_info_t *authn_info;

    authn_info = apr_hash_get(ctx->server_authn_info, conn->host_url,
                              APR_HASH_KEY_STRING);

    if (!authn_info) {
        authn_info = apr_pcalloc(ctx->pool, sizeof(serf__authn_info_t));
        apr_hash_set(ctx->server_authn_info,
                     apr_pstrdup(ctx->pool, conn->host_url),
                     APR_HASH_KEY_STRING, authn_info);
    }

    return authn_info;
}