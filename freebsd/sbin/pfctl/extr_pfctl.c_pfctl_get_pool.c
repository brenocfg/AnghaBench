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
typedef  scalar_t__ u_int32_t ;
struct pfioc_pooladdr {int r_action; scalar_t__ nr; int /*<<< orphan*/  addr; scalar_t__ ticket; scalar_t__ r_num; int /*<<< orphan*/  anchor; } ;
struct pf_pooladdr {int dummy; } ;
struct pf_pool {int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  pp ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGETADDR ; 
 int /*<<< orphan*/  DIOCGETADDRS ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pf_pooladdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,struct pf_pooladdr*,int) ; 
 struct pf_pooladdr* calloc (int,int) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct pfioc_pooladdr*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct pfioc_pooladdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  warn (char*) ; 

int
pfctl_get_pool(int dev, struct pf_pool *pool, u_int32_t nr,
    u_int32_t ticket, int r_action, char *anchorname)
{
	struct pfioc_pooladdr pp;
	struct pf_pooladdr *pa;
	u_int32_t pnr, mpnr;

	memset(&pp, 0, sizeof(pp));
	memcpy(pp.anchor, anchorname, sizeof(pp.anchor));
	pp.r_action = r_action;
	pp.r_num = nr;
	pp.ticket = ticket;
	if (ioctl(dev, DIOCGETADDRS, &pp)) {
		warn("DIOCGETADDRS");
		return (-1);
	}
	mpnr = pp.nr;
	TAILQ_INIT(&pool->list);
	for (pnr = 0; pnr < mpnr; ++pnr) {
		pp.nr = pnr;
		if (ioctl(dev, DIOCGETADDR, &pp)) {
			warn("DIOCGETADDR");
			return (-1);
		}
		pa = calloc(1, sizeof(struct pf_pooladdr));
		if (pa == NULL)
			err(1, "calloc");
		bcopy(&pp.addr, pa, sizeof(struct pf_pooladdr));
		TAILQ_INSERT_TAIL(&pool->list, pa, entries);
	}

	return (0);
}