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
struct dctcp {scalar_t__ num_cong_events; scalar_t__ ece_prev; scalar_t__ ece_curr; scalar_t__ ce_prev; scalar_t__ save_sndnxt; int /*<<< orphan*/  alpha; scalar_t__ bytes_total; scalar_t__ bytes_ecn; } ;
struct cc_var {struct dctcp* cc_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  M_dctcp ; 
 int /*<<< orphan*/  V_dctcp_alpha ; 
 struct dctcp* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
dctcp_cb_init(struct cc_var *ccv)
{
	struct dctcp *dctcp_data;

	dctcp_data = malloc(sizeof(struct dctcp), M_dctcp, M_NOWAIT|M_ZERO);

	if (dctcp_data == NULL)
		return (ENOMEM);

	/* Initialize some key variables with sensible defaults. */
	dctcp_data->bytes_ecn = 0;
	dctcp_data->bytes_total = 0;
	/*
	 * When alpha is set to 0 in the beginning, DCTCP sender transfers as
	 * much data as possible until the value converges which may expand the
	 * queueing delay at the switch. When alpha is set to 1, queueing delay
	 * is kept small.
	 * Throughput-sensitive applications should have alpha = 0
	 * Latency-sensitive applications should have alpha = 1
	 *
	 * Note: DCTCP draft suggests initial alpha to be 1 but we've decided to
	 * keep it 0 as default.
	 */
	dctcp_data->alpha = V_dctcp_alpha;
	dctcp_data->save_sndnxt = 0;
	dctcp_data->ce_prev = 0;
	dctcp_data->ece_curr = 0;
	dctcp_data->ece_prev = 0;
	dctcp_data->num_cong_events = 0;

	ccv->cc_data = dctcp_data;
	return (0);
}