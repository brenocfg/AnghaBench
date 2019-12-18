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
struct chd {int /*<<< orphan*/  shadow_w; scalar_t__ loss_compete; scalar_t__ maxrtt_in_rtt; scalar_t__ prev_backoff_qdly; } ;
struct cc_var {struct chd* cc_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCV (struct cc_var*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cwnd ; 

__attribute__((used)) static void
chd_conn_init(struct cc_var *ccv)
{
	struct chd *chd_data;

	chd_data = ccv->cc_data;
	chd_data->prev_backoff_qdly = 0;
	chd_data->maxrtt_in_rtt = 0;
	chd_data->loss_compete = 0;
	/*
	 * Initialise the shadow_cwnd to be equal to snd_cwnd in case we are
	 * competing with loss based flows from the start.
	 */
	chd_data->shadow_w = CCV(ccv, snd_cwnd);
}