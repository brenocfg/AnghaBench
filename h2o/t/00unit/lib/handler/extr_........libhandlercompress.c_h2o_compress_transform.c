#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  len; TYPE_1__* callbacks; } ;
typedef  TYPE_2__ h2o_sendvec_t ;
typedef  int /*<<< orphan*/  h2o_send_state_t ;
typedef  int /*<<< orphan*/  h2o_req_t ;
struct TYPE_15__ {int /*<<< orphan*/  (* do_transform ) (TYPE_3__*,TYPE_2__*,size_t,int /*<<< orphan*/ ,TYPE_2__**,size_t*) ;int /*<<< orphan*/ * push_buf; } ;
typedef  TYPE_3__ h2o_compress_context_t ;
struct TYPE_13__ {int /*<<< orphan*/  (* flatten ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_PULL_SENDVEC_MAX_SIZE ; 
 int /*<<< orphan*/  H2O_SEND_STATE_ERROR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * h2o_mem_alloc (int /*<<< orphan*/ ) ; 
 scalar_t__ h2o_send_state_is_in_progress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_sendvec_flatten_raw (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_sendvec_init_raw (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,TYPE_2__*,size_t,int /*<<< orphan*/ ,TYPE_2__**,size_t*) ; 

h2o_send_state_t h2o_compress_transform(h2o_compress_context_t *self, h2o_req_t *req, h2o_sendvec_t *inbufs, size_t inbufcnt,
                                        h2o_send_state_t state, h2o_sendvec_t **outbufs, size_t *outbufcnt)
{
    h2o_sendvec_t flattened;

    if (inbufcnt != 0 && inbufs->callbacks->flatten != &h2o_sendvec_flatten_raw) {
        assert(inbufcnt == 1);
        assert(inbufs->len <= H2O_PULL_SENDVEC_MAX_SIZE);
        if (self->push_buf == NULL)
            self->push_buf = h2o_mem_alloc(h2o_send_state_is_in_progress(state) ? H2O_PULL_SENDVEC_MAX_SIZE : inbufs->len);
        if (!(*inbufs->callbacks->flatten)(inbufs, req, h2o_iovec_init(self->push_buf, inbufs->len), 0)) {
            *outbufs = NULL;
            *outbufcnt = 0;
            return H2O_SEND_STATE_ERROR;
        }
        h2o_sendvec_init_raw(&flattened, self->push_buf, inbufs->len);
        inbufs = &flattened;
    }

    return self->do_transform(self, inbufs, inbufcnt, state, outbufs, outbufcnt);
}