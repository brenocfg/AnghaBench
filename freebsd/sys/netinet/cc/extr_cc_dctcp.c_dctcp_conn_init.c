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
struct dctcp {int save_sndnxt; } ;
struct cc_var {struct dctcp* cc_data; } ;

/* Variables and functions */
 int CCV (struct cc_var*,int /*<<< orphan*/ ) ; 
 int TF_ECN_PERMIT ; 
 int /*<<< orphan*/  snd_nxt ; 
 int /*<<< orphan*/  t_flags ; 

__attribute__((used)) static void
dctcp_conn_init(struct cc_var *ccv)
{
	struct dctcp *dctcp_data;

	dctcp_data = ccv->cc_data;

	if (CCV(ccv, t_flags) & TF_ECN_PERMIT)
		dctcp_data->save_sndnxt = CCV(ccv, snd_nxt);
}