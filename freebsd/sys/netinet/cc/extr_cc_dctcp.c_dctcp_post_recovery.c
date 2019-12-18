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
struct cc_var {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* post_recovery ) (struct cc_var*) ;} ;

/* Variables and functions */
 int CCV (struct cc_var*,int /*<<< orphan*/ ) ; 
 int TF_ECN_PERMIT ; 
 int /*<<< orphan*/  dctcp_update_alpha (struct cc_var*) ; 
 TYPE_1__ newreno_cc_algo ; 
 int /*<<< orphan*/  stub1 (struct cc_var*) ; 
 int /*<<< orphan*/  t_flags ; 

__attribute__((used)) static void
dctcp_post_recovery(struct cc_var *ccv)
{
	newreno_cc_algo.post_recovery(ccv);

	if (CCV(ccv, t_flags) & TF_ECN_PERMIT)
		dctcp_update_alpha(ccv);
}