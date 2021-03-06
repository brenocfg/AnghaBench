#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct st_compress_encoder_t {int /*<<< orphan*/  super; int /*<<< orphan*/  compressor; } ;
typedef  int /*<<< orphan*/  h2o_sendvec_t ;
typedef  int /*<<< orphan*/  h2o_send_state_t ;
typedef  int /*<<< orphan*/  h2o_req_t ;
typedef  int /*<<< orphan*/  h2o_ostream_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_compress_transform (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  h2o_ostream_send_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ h2o_send_state_is_in_progress (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_send(h2o_ostream_t *_self, h2o_req_t *req, h2o_sendvec_t *inbufs, size_t inbufcnt, h2o_send_state_t state)
{
    struct st_compress_encoder_t *self = (void *)_self;
    h2o_sendvec_t *outbufs;
    size_t outbufcnt;

    if (inbufcnt == 0 && h2o_send_state_is_in_progress(state)) {
        h2o_ostream_send_next(&self->super, req, inbufs, inbufcnt, state);
        return;
    }

    state = h2o_compress_transform(self->compressor, req, inbufs, inbufcnt, state, &outbufs, &outbufcnt);
    h2o_ostream_send_next(&self->super, req, outbufs, outbufcnt, state);
}