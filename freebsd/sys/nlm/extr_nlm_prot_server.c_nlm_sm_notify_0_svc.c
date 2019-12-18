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
struct svc_req {int dummy; } ;
struct nlm_sm_status {int dummy; } ;
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  nlm_sm_notify (struct nlm_sm_status*) ; 

bool_t
nlm_sm_notify_0_svc(struct nlm_sm_status *argp, void *result, struct svc_req *rqstp)
{
	nlm_sm_notify(argp);

	return (TRUE);
}