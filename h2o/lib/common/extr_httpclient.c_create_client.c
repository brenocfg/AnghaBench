#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_mem_pool_t ;
struct TYPE_8__ {int /*<<< orphan*/  cb; } ;
struct TYPE_7__ {int /*<<< orphan*/  on_connect; } ;
struct TYPE_9__ {TYPE_2__ _timeout; TYPE_1__ _cb; int /*<<< orphan*/ * write_req; int /*<<< orphan*/ * update_window; int /*<<< orphan*/ * get_socket; int /*<<< orphan*/ * steal_socket; int /*<<< orphan*/  cancel; void* data; int /*<<< orphan*/ * ctx; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_3__ h2o_httpclient_t ;
typedef  int /*<<< orphan*/  h2o_httpclient_ctx_t ;
typedef  int /*<<< orphan*/  h2o_httpclient_connect_cb ;

/* Variables and functions */
 size_t SZ_MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_cancel ; 
 int /*<<< orphan*/  h2o_httpclient__h1_size ; 
 int /*<<< orphan*/  h2o_httpclient__h2_size ; 
 TYPE_3__* h2o_mem_alloc (size_t) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  on_connect_timeout ; 

__attribute__((used)) static h2o_httpclient_t *create_client(h2o_mem_pool_t *pool, void *data, h2o_httpclient_ctx_t *ctx,
                                       h2o_httpclient_connect_cb on_connect)
{
#define SZ_MAX(x, y) ((x) > (y) ? (x) : (y))
    size_t sz = SZ_MAX(h2o_httpclient__h1_size, h2o_httpclient__h2_size);
#undef SZ_MAX
    h2o_httpclient_t *client = h2o_mem_alloc(sz);
    memset(client, 0, sz);
    client->pool = pool;
    client->ctx = ctx;
    client->data = data;
    client->cancel = do_cancel;
    client->steal_socket = NULL;
    client->get_socket = NULL;
    client->update_window = NULL;
    client->write_req = NULL;
    client->_cb.on_connect = on_connect;
    client->_timeout.cb = on_connect_timeout;

    return client;
}