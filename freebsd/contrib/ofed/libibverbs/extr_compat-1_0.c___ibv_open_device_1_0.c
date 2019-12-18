#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ibv_device_1_0 {int /*<<< orphan*/  real_device; } ;
struct TYPE_2__ {int /*<<< orphan*/  post_srq_recv; int /*<<< orphan*/  post_recv; int /*<<< orphan*/  post_send; int /*<<< orphan*/  req_notify_cq; int /*<<< orphan*/  poll_cq; } ;
struct ibv_context_1_0 {TYPE_1__ ops; struct ibv_context* real_context; struct ibv_device_1_0* device; } ;
struct ibv_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ibv_context_1_0*) ; 
 struct ibv_context* ibv_open_device (int /*<<< orphan*/ ) ; 
 struct ibv_context_1_0* malloc (int) ; 
 int /*<<< orphan*/  poll_cq_wrapper_1_0 ; 
 int /*<<< orphan*/  post_recv_wrapper_1_0 ; 
 int /*<<< orphan*/  post_send_wrapper_1_0 ; 
 int /*<<< orphan*/  post_srq_recv_wrapper_1_0 ; 
 int /*<<< orphan*/  req_notify_cq_wrapper_1_0 ; 

struct ibv_context_1_0 *__ibv_open_device_1_0(struct ibv_device_1_0 *device)
{
	struct ibv_context     *real_ctx;
	struct ibv_context_1_0 *ctx;

	ctx = malloc(sizeof *ctx);
	if (!ctx)
		return NULL;

	real_ctx = ibv_open_device(device->real_device);
	if (!real_ctx) {
		free(ctx);
		return NULL;
	}

	ctx->device       = device;
	ctx->real_context = real_ctx;

	ctx->ops.poll_cq       = poll_cq_wrapper_1_0;
	ctx->ops.req_notify_cq = req_notify_cq_wrapper_1_0;
	ctx->ops.post_send     = post_send_wrapper_1_0;
	ctx->ops.post_recv     = post_recv_wrapper_1_0;
	ctx->ops.post_srq_recv = post_srq_recv_wrapper_1_0;

	return ctx;
}