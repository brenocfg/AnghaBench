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
struct cdg {int /*<<< orphan*/  shadow_w; } ;
struct cc_var {struct cdg* cc_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCV (struct cc_var*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cwnd ; 

__attribute__((used)) static void
cdg_conn_init(struct cc_var *ccv)
{
	struct cdg *cdg_data = ccv->cc_data;

	/*
	 * Initialise the shadow_cwnd in case we are competing with loss based
	 * flows from the start
	 */
	cdg_data->shadow_w = CCV(ccv, snd_cwnd);
}