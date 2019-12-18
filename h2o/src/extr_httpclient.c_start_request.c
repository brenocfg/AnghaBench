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
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_url_t ;
typedef  int /*<<< orphan*/  h2o_socketpool_target_t ;
typedef  int /*<<< orphan*/  h2o_socketpool_t ;
struct TYPE_7__ {int /*<<< orphan*/  loop; int /*<<< orphan*/ * http3; } ;
typedef  TYPE_1__ h2o_httpclient_ctx_t ;
struct TYPE_8__ {int /*<<< orphan*/  body_size; int /*<<< orphan*/  url; } ;
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 char* CA_PATH ; 
 int /*<<< orphan*/  H2O_ROOT ; 
 char* H2O_TO_STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IO_TIMEOUT ; 
 int /*<<< orphan*/  SIZE_MAX ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_load_verify_locations (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_verify (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int SSL_VERIFY_FAIL_IF_NO_PEER_CERT ; 
 int SSL_VERIFY_NONE ; 
 int SSL_VERIFY_PEER ; 
 int /*<<< orphan*/  TLSv1_client_method () ; 
 int /*<<< orphan*/ * connpool ; 
 int /*<<< orphan*/  cur_req_body_size ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  h2o_httpclient_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_httpclient_connect_h3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_httpclient_connection_pool_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* h2o_mem_alloc (int) ; 
 int /*<<< orphan*/ * h2o_mem_alloc_pool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  h2o_mem_clear_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * h2o_socketpool_create_target (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_socketpool_init_specific (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_socketpool_register_loop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socketpool_set_ssl_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_socketpool_set_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ h2o_url_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_connect ; 
 int /*<<< orphan*/  on_error (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pool ; 
 TYPE_3__ req ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 scalar_t__ ssl_verify_none ; 
 int strlen (char*) ; 

__attribute__((used)) static void start_request(h2o_httpclient_ctx_t *ctx)
{
    h2o_url_t *url_parsed;

    /* clear memory pool */
    h2o_mem_clear_pool(&pool);

    /* parse URL */
    url_parsed = h2o_mem_alloc_pool(&pool, *url_parsed, 1);
    if (h2o_url_parse(req.url, SIZE_MAX, url_parsed) != 0) {
        on_error(ctx, "unrecognized type of URL: %s", req.url);
        return;
    }

    cur_req_body_size = req.body_size;

    /* initiate the request */
    if (ctx->http3 != NULL) {
        h2o_httpclient_connect_h3(NULL, &pool, url_parsed, ctx, url_parsed, on_connect);
    } else {
        if (connpool == NULL) {
            connpool = h2o_mem_alloc(sizeof(*connpool));
            h2o_socketpool_t *sockpool = h2o_mem_alloc(sizeof(*sockpool));
            h2o_socketpool_target_t *target = h2o_socketpool_create_target(url_parsed, NULL);
            h2o_socketpool_init_specific(sockpool, 10, &target, 1, NULL);
            h2o_socketpool_set_timeout(sockpool, IO_TIMEOUT);
            h2o_socketpool_register_loop(sockpool, ctx->loop);
            h2o_httpclient_connection_pool_init(connpool, sockpool);

            /* obtain root */
            char *root, *crt_fullpath;
            if ((root = getenv("H2O_ROOT")) == NULL)
                root = H2O_TO_STR(H2O_ROOT);
#define CA_PATH "/share/h2o/ca-bundle.crt"
            crt_fullpath = h2o_mem_alloc(strlen(root) + strlen(CA_PATH) + 1);
            sprintf(crt_fullpath, "%s%s", root, CA_PATH);
#undef CA_PATH

            SSL_CTX *ssl_ctx = SSL_CTX_new(TLSv1_client_method());
            SSL_CTX_load_verify_locations(ssl_ctx, crt_fullpath, NULL);
            if (ssl_verify_none) {
                SSL_CTX_set_verify(ssl_ctx, SSL_VERIFY_NONE, NULL);
            } else {
                SSL_CTX_set_verify(ssl_ctx, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, NULL);
            }
            h2o_socketpool_set_ssl_ctx(sockpool, ssl_ctx);
            SSL_CTX_free(ssl_ctx);
        }
        h2o_httpclient_connect(NULL, &pool, url_parsed, ctx, connpool, url_parsed, on_connect);
    }
}