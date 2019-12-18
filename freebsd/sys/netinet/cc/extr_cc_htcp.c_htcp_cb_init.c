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
struct htcp {int /*<<< orphan*/  t_last_cong; scalar_t__ prev_cwnd; void* minrtt; void* maxrtt; int /*<<< orphan*/  beta; int /*<<< orphan*/  alpha; } ;
struct cc_var {struct htcp* cc_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HTCP_INIT_ALPHA ; 
 int /*<<< orphan*/  HTCP_MINBETA ; 
 int /*<<< orphan*/  M_HTCP ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 void* TCPTV_SRTTBASE ; 
 struct htcp* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ticks ; 

__attribute__((used)) static int
htcp_cb_init(struct cc_var *ccv)
{
	struct htcp *htcp_data;

	htcp_data = malloc(sizeof(struct htcp), M_HTCP, M_NOWAIT);

	if (htcp_data == NULL)
		return (ENOMEM);

	/* Init some key variables with sensible defaults. */
	htcp_data->alpha = HTCP_INIT_ALPHA;
	htcp_data->beta = HTCP_MINBETA;
	htcp_data->maxrtt = TCPTV_SRTTBASE;
	htcp_data->minrtt = TCPTV_SRTTBASE;
	htcp_data->prev_cwnd = 0;
	htcp_data->t_last_cong = ticks;

	ccv->cc_data = htcp_data;

	return (0);
}