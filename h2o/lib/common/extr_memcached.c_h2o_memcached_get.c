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
typedef  int /*<<< orphan*/  h2o_multithread_receiver_t ;
struct TYPE_8__ {int value_is_encoded; void* cb_data; int /*<<< orphan*/  cb; int /*<<< orphan*/ * receiver; } ;
struct TYPE_7__ {TYPE_2__ get; } ;
struct TYPE_9__ {TYPE_1__ data; } ;
typedef  TYPE_3__ h2o_memcached_req_t ;
typedef  int /*<<< orphan*/  h2o_memcached_get_cb ;
typedef  int /*<<< orphan*/  h2o_memcached_context_t ;
typedef  int /*<<< orphan*/  h2o_iovec_t ;

/* Variables and functions */
 int H2O_MEMCACHED_ENCODE_KEY ; 
 int H2O_MEMCACHED_ENCODE_VALUE ; 
 int /*<<< orphan*/  REQ_TYPE_GET ; 
 TYPE_3__* create_req (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dispatch (int /*<<< orphan*/ *,TYPE_3__*) ; 

h2o_memcached_req_t *h2o_memcached_get(h2o_memcached_context_t *ctx, h2o_multithread_receiver_t *receiver, h2o_iovec_t key,
                                       h2o_memcached_get_cb cb, void *cb_data, int flags)
{
    h2o_memcached_req_t *req = create_req(ctx, REQ_TYPE_GET, key, (flags & H2O_MEMCACHED_ENCODE_KEY) != 0);
    req->data.get.receiver = receiver;
    req->data.get.cb = cb;
    req->data.get.cb_data = cb_data;
    req->data.get.value_is_encoded = (flags & H2O_MEMCACHED_ENCODE_VALUE) != 0;
    dispatch(ctx, req);
    return req;
}