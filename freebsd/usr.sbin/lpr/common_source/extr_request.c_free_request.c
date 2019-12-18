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
struct request {int /*<<< orphan*/  jobids; int /*<<< orphan*/  users; struct req_user* authinfo; struct req_user* prettyname; struct req_user* authname; struct req_user* logname; } ;
struct req_user {int dummy; } ;
typedef  struct req_user req_jobid ;

/* Variables and functions */
 struct req_user* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct req_user*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct req_user*) ; 
 int /*<<< orphan*/  init_request (struct request*) ; 
 int /*<<< orphan*/  rj_link ; 
 int /*<<< orphan*/  ru_link ; 

void
free_request(struct request *rp)
{
	struct req_user *ru;
	struct req_jobid *rj;

	if (rp->logname)
		free(rp->logname);
	if (rp->authname)
		free(rp->authname);
	if (rp->prettyname)
		free(rp->prettyname);
	if (rp->authinfo)
		free(rp->authinfo);
	while ((ru = TAILQ_FIRST(&rp->users)) != NULL) {
		TAILQ_REMOVE(&rp->users, ru, ru_link);
		free(ru);
	}
	while ((rj = TAILQ_FIRST(&rp->jobids)) != NULL) {
		TAILQ_REMOVE(&rp->jobids, rj, rj_link);
		free(rj);
	}
	init_request(rp);
}