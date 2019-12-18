#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct svc_req {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  stat; } ;
struct TYPE_5__ {TYPE_1__ stat; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_2__ nlm4_res ;

/* Variables and functions */
 int /*<<< orphan*/  NLM_VERS4 ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  lock_answer (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_from_addr (char*,struct svc_req*) ; 

void *
nlm4_lock_res_4_svc(nlm4_res *arg, struct svc_req *rqstp)
{
	if (debug_level)
		log_from_addr("nlm4_lock_res", rqstp);

	(void)lock_answer(-1, &arg->cookie, arg->stat.stat, NULL, NLM_VERS4);

	return (NULL);
}