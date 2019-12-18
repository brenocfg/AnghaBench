#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * pending; } ;
struct TYPE_6__ {int /*<<< orphan*/ * pending; } ;
struct TYPE_8__ {int /*<<< orphan*/  allocator; int /*<<< orphan*/  ctx; int /*<<< orphan*/  biom; int /*<<< orphan*/  ssl; TYPE_2__ encrypt; TYPE_1__ decrypt; } ;
typedef  TYPE_3__ serf_ssl_context_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_meth_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serf_bucket_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serf_bucket_mem_free (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static apr_status_t ssl_free_context(
    serf_ssl_context_t *ssl_ctx)
{
    /* If never had the pending buckets, don't try to free them. */
    if (ssl_ctx->decrypt.pending != NULL) {
        serf_bucket_destroy(ssl_ctx->decrypt.pending);
    }
    if (ssl_ctx->encrypt.pending != NULL) {
        serf_bucket_destroy(ssl_ctx->encrypt.pending);
    }

    /* SSL_free implicitly frees the underlying BIO. */
    SSL_free(ssl_ctx->ssl);
    bio_meth_free(ssl_ctx->biom);
    SSL_CTX_free(ssl_ctx->ctx);

    serf_bucket_mem_free(ssl_ctx->allocator, ssl_ctx);

    return APR_SUCCESS;
}