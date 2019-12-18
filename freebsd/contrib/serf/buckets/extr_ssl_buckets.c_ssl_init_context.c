#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_3__* read_baton; int /*<<< orphan*/  read; } ;
struct TYPE_11__ {TYPE_5__ databuf; void* status; void* pending; int /*<<< orphan*/ * stream; } ;
struct TYPE_10__ {TYPE_5__ databuf; void* status; void* pending; int /*<<< orphan*/ * stream_next; int /*<<< orphan*/ * stream; } ;
struct TYPE_12__ {TYPE_2__ decrypt; TYPE_1__ encrypt; int /*<<< orphan*/  ctx; int /*<<< orphan*/  ssl; int /*<<< orphan*/  bio; int /*<<< orphan*/  biom; int /*<<< orphan*/ * server_cert_chain_callback; int /*<<< orphan*/ * server_cert_callback; int /*<<< orphan*/ * cert_pw_callback; int /*<<< orphan*/ * cert_callback; void* fatal_err; void* pending_err; scalar_t__ cached_cert_pw; scalar_t__ cached_cert; int /*<<< orphan*/ * allocator; int /*<<< orphan*/  pool; scalar_t__ refcount; } ;
typedef  TYPE_3__ serf_ssl_context_t ;
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;

/* Variables and functions */
 void* APR_SUCCESS ; 
 int /*<<< orphan*/  BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_client_cert_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_info_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_options (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_verify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SSL_OP_ALL ; 
 int SSL_OP_NO_SSLv2 ; 
 int SSL_OP_NO_SSLv3 ; 
 int /*<<< orphan*/  SSL_VERIFY_PEER ; 
 int /*<<< orphan*/  SSL_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_app_data (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  SSL_set_bio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_connect_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSLv23_client_method () ; 
 int /*<<< orphan*/  apps_ssl_info_callback ; 
 int /*<<< orphan*/  bio_meth_bucket_new () ; 
 int /*<<< orphan*/  bio_set_data (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  disable_compression (TYPE_3__*) ; 
 int /*<<< orphan*/  init_ssl_libraries () ; 
 void* serf_bucket_aggregate_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serf_bucket_allocator_get_pool (int /*<<< orphan*/ *) ; 
 TYPE_3__* serf_bucket_mem_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  serf_databuf_init (TYPE_5__*) ; 
 int /*<<< orphan*/  ssl_decrypt ; 
 int /*<<< orphan*/  ssl_encrypt ; 
 int /*<<< orphan*/  ssl_need_client_cert ; 
 int /*<<< orphan*/  validate_server_certificate ; 

__attribute__((used)) static serf_ssl_context_t *ssl_init_context(serf_bucket_alloc_t *allocator)
{
    serf_ssl_context_t *ssl_ctx;

    init_ssl_libraries();

    ssl_ctx = serf_bucket_mem_alloc(allocator, sizeof(*ssl_ctx));

    ssl_ctx->refcount = 0;
    ssl_ctx->pool = serf_bucket_allocator_get_pool(allocator);
    ssl_ctx->allocator = allocator;

    /* Use the best possible protocol version, but disable the broken SSLv2/3 */
    ssl_ctx->ctx = SSL_CTX_new(SSLv23_client_method());
    SSL_CTX_set_options(ssl_ctx->ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3);

    SSL_CTX_set_client_cert_cb(ssl_ctx->ctx, ssl_need_client_cert);
    ssl_ctx->cached_cert = 0;
    ssl_ctx->cached_cert_pw = 0;
    ssl_ctx->pending_err = APR_SUCCESS;
    ssl_ctx->fatal_err = APR_SUCCESS;

    ssl_ctx->cert_callback = NULL;
    ssl_ctx->cert_pw_callback = NULL;
    ssl_ctx->server_cert_callback = NULL;
    ssl_ctx->server_cert_chain_callback = NULL;

    SSL_CTX_set_verify(ssl_ctx->ctx, SSL_VERIFY_PEER,
                       validate_server_certificate);
    SSL_CTX_set_options(ssl_ctx->ctx, SSL_OP_ALL);
    /* Disable SSL compression by default. */
    disable_compression(ssl_ctx);

    ssl_ctx->ssl = SSL_new(ssl_ctx->ctx);
    ssl_ctx->biom = bio_meth_bucket_new();
    ssl_ctx->bio = BIO_new(ssl_ctx->biom);
    bio_set_data(ssl_ctx->bio, ssl_ctx);

    SSL_set_bio(ssl_ctx->ssl, ssl_ctx->bio, ssl_ctx->bio);

    SSL_set_connect_state(ssl_ctx->ssl);

    SSL_set_app_data(ssl_ctx->ssl, ssl_ctx);

#if SSL_VERBOSE
    SSL_CTX_set_info_callback(ssl_ctx->ctx, apps_ssl_info_callback);
#endif

    ssl_ctx->encrypt.stream = NULL;
    ssl_ctx->encrypt.stream_next = NULL;
    ssl_ctx->encrypt.pending = serf_bucket_aggregate_create(allocator);
    ssl_ctx->encrypt.status = APR_SUCCESS;
    serf_databuf_init(&ssl_ctx->encrypt.databuf);
    ssl_ctx->encrypt.databuf.read = ssl_encrypt;
    ssl_ctx->encrypt.databuf.read_baton = ssl_ctx;

    ssl_ctx->decrypt.stream = NULL;
    ssl_ctx->decrypt.pending = serf_bucket_aggregate_create(allocator);
    ssl_ctx->decrypt.status = APR_SUCCESS;
    serf_databuf_init(&ssl_ctx->decrypt.databuf);
    ssl_ctx->decrypt.databuf.read = ssl_decrypt;
    ssl_ctx->decrypt.databuf.read_baton = ssl_ctx;

    return ssl_ctx;
}