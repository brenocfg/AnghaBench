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
struct dh_ctx {void* g; void* q; void* p; } ;
struct dh {int p_size; int q_size; int g_size; scalar_t__ g; scalar_t__ q; scalar_t__ p; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ dh_check_params_length (int) ; 
 void* mpi_read_raw_data (scalar_t__,int) ; 

__attribute__((used)) static int dh_set_params(struct dh_ctx *ctx, struct dh *params)
{
	if (dh_check_params_length(params->p_size << 3))
		return -EINVAL;

	ctx->p = mpi_read_raw_data(params->p, params->p_size);
	if (!ctx->p)
		return -EINVAL;

	if (params->q && params->q_size) {
		ctx->q = mpi_read_raw_data(params->q, params->q_size);
		if (!ctx->q)
			return -EINVAL;
	}

	ctx->g = mpi_read_raw_data(params->g, params->g_size);
	if (!ctx->g)
		return -EINVAL;

	return 0;
}