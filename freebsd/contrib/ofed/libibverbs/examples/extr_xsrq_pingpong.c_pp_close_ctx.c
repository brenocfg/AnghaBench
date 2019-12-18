#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int num_clients; scalar_t__ fd; TYPE_1__* recv_qp; TYPE_1__* send_qp; TYPE_1__* rem_dest; TYPE_1__* buf; int /*<<< orphan*/  context; scalar_t__ channel; int /*<<< orphan*/  pd; int /*<<< orphan*/  mr; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; scalar_t__ xrcd; int /*<<< orphan*/  srq; } ;
struct TYPE_4__ {scalar_t__ sockfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (scalar_t__) ; 
 TYPE_3__ ctx ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ ibv_close_device (int /*<<< orphan*/ ) ; 
 scalar_t__ ibv_close_xrcd (scalar_t__) ; 
 scalar_t__ ibv_dealloc_pd (int /*<<< orphan*/ ) ; 
 scalar_t__ ibv_dereg_mr (int /*<<< orphan*/ ) ; 
 scalar_t__ ibv_destroy_comp_channel (scalar_t__) ; 
 scalar_t__ ibv_destroy_cq (int /*<<< orphan*/ ) ; 
 scalar_t__ ibv_destroy_qp (TYPE_1__) ; 
 scalar_t__ ibv_destroy_srq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int pp_close_ctx(void)
{
	int i;

	for (i = 0; i < ctx.num_clients; ++i) {

		if (ibv_destroy_qp(ctx.send_qp[i])) {
			fprintf(stderr, "Couldn't destroy INI QP[%d]\n", i);
			return 1;
		}

		if (ibv_destroy_qp(ctx.recv_qp[i])) {
			fprintf(stderr, "Couldn't destroy TGT QP[%d]\n", i);
			return 1;
		}

		if (ctx.rem_dest[i].sockfd)
			close(ctx.rem_dest[i].sockfd);
	}

	if (ibv_destroy_srq(ctx.srq)) {
		fprintf(stderr, "Couldn't destroy SRQ\n");
		return 1;
	}

	if (ctx.xrcd && ibv_close_xrcd(ctx.xrcd)) {
		fprintf(stderr, "Couldn't close the XRC Domain\n");
		return 1;
	}
	if (ctx.fd >= 0 && close(ctx.fd)) {
		fprintf(stderr, "Couldn't close the file for the XRC Domain\n");
		return 1;
	}

	if (ibv_destroy_cq(ctx.send_cq)) {
		fprintf(stderr, "Couldn't destroy send CQ\n");
		return 1;
	}

	if (ibv_destroy_cq(ctx.recv_cq)) {
		fprintf(stderr, "Couldn't destroy recv CQ\n");
		return 1;
	}

	if (ibv_dereg_mr(ctx.mr)) {
		fprintf(stderr, "Couldn't deregister MR\n");
		return 1;
	}

	if (ibv_dealloc_pd(ctx.pd)) {
		fprintf(stderr, "Couldn't deallocate PD\n");
		return 1;
	}

	if (ctx.channel) {
		if (ibv_destroy_comp_channel(ctx.channel)) {
			fprintf(stderr,
				"Couldn't destroy completion channel\n");
			return 1;
		}
	}

	if (ibv_close_device(ctx.context)) {
		fprintf(stderr, "Couldn't release context\n");
		return 1;
	}

	free(ctx.buf);
	free(ctx.rem_dest);
	free(ctx.send_qp);
	free(ctx.recv_qp);
	return 0;
}