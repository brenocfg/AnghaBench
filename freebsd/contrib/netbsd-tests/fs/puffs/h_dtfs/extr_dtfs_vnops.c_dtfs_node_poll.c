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
struct puffs_usermount {int dummy; } ;
struct TYPE_2__ {int tv_sec; } ;
struct itimerval {TYPE_1__ it_value; } ;
struct dtfs_poll {int /*<<< orphan*/  dp_pcc; } ;
struct dtfs_mount {int /*<<< orphan*/  dtm_pollent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct dtfs_poll*,int /*<<< orphan*/ ) ; 
 int POLLIN ; 
 int POLLOUT ; 
 int POLLRDNORM ; 
 int POLLWRNORM ; 
 int /*<<< orphan*/  dp_entries ; 
 int errno ; 
 int /*<<< orphan*/  memset (struct itimerval*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  puffs_cc_getcc (struct puffs_usermount*) ; 
 int /*<<< orphan*/  puffs_cc_yield (int /*<<< orphan*/ ) ; 
 struct dtfs_mount* puffs_getspecific (struct puffs_usermount*) ; 
 int setitimer (int /*<<< orphan*/ ,struct itimerval*,int /*<<< orphan*/ *) ; 

int
dtfs_node_poll(struct puffs_usermount *pu, void *opc, int *events)
{
	struct dtfs_mount *dtm = puffs_getspecific(pu);
	struct dtfs_poll dp;
	struct itimerval it;

	memset(&it, 0, sizeof(struct itimerval));
	it.it_value.tv_sec = 4;
	if (setitimer(ITIMER_REAL, &it, NULL) == -1)
		return errno;

	dp.dp_pcc = puffs_cc_getcc(pu);
	LIST_INSERT_HEAD(&dtm->dtm_pollent, &dp, dp_entries);
	puffs_cc_yield(dp.dp_pcc);

	*events = *events & (POLLIN | POLLOUT | POLLRDNORM | POLLWRNORM);
	return 0;
}