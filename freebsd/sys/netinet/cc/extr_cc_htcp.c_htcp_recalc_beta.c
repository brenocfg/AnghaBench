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
struct htcp {int minrtt; int maxrtt; int /*<<< orphan*/  beta; } ;
struct cc_var {struct htcp* cc_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HTCP_MAXBETA ; 
 int /*<<< orphan*/  HTCP_MINBETA ; 
 int HTCP_SHIFT ; 
 int TCPTV_SRTTBASE ; 
 scalar_t__ V_htcp_adaptive_backoff ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
htcp_recalc_beta(struct cc_var *ccv)
{
	struct htcp *htcp_data;

	htcp_data = ccv->cc_data;

	/*
	 * TCPTV_SRTTBASE is the initialised value of each connection's SRTT, so
	 * we only calc beta if the connection's SRTT has been changed from its
	 * initial value. beta is bounded to ensure it is always between
	 * HTCP_MINBETA and HTCP_MAXBETA.
	 */
	if (V_htcp_adaptive_backoff && htcp_data->minrtt != TCPTV_SRTTBASE &&
	    htcp_data->maxrtt != TCPTV_SRTTBASE)
		htcp_data->beta = min(max(HTCP_MINBETA,
		    (htcp_data->minrtt << HTCP_SHIFT) / htcp_data->maxrtt),
		    HTCP_MAXBETA);
	else
		htcp_data->beta = HTCP_MINBETA;
}