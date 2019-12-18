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
struct ibv_pd {int dummy; } ;
struct ibv_context {int dummy; } ;
struct ibv_alloc_pd {int dummy; } ;
struct c4iw_pd {struct ibv_pd ibv_pd; } ;
struct c4iw_alloc_pd_resp {int /*<<< orphan*/  ibv_resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct c4iw_pd*) ; 
 scalar_t__ ibv_cmd_alloc_pd (struct ibv_context*,struct ibv_pd*,struct ibv_alloc_pd*,int,int /*<<< orphan*/ *,int) ; 
 struct c4iw_pd* malloc (int) ; 

struct ibv_pd *c4iw_alloc_pd(struct ibv_context *context)
{
	struct ibv_alloc_pd cmd;
	struct c4iw_alloc_pd_resp resp;
	struct c4iw_pd *pd;

	pd = malloc(sizeof *pd);
	if (!pd)
		return NULL;

	if (ibv_cmd_alloc_pd(context, &pd->ibv_pd, &cmd, sizeof cmd,
			     &resp.ibv_resp, sizeof resp)) {
		free(pd);
		return NULL;
	}

	return &pd->ibv_pd;
}