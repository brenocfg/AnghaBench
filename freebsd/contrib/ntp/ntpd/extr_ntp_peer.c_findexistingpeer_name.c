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
typedef  scalar_t__ u_short ;
struct peer {int hmode; int /*<<< orphan*/ * hostname; int /*<<< orphan*/  srcadr; struct peer* p_link; } ;

/* Variables and functions */
 scalar_t__ AF (int /*<<< orphan*/ *) ; 
 scalar_t__ AF_UNSPEC ; 
 struct peer* peer_list ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static struct peer *
findexistingpeer_name(
	const char *	hostname,
	u_short		hname_fam,
	struct peer *	start_peer,
	int		mode
	)
{
	struct peer *p;

	if (NULL == start_peer)
		p = peer_list;
	else
		p = start_peer->p_link;
	for (; p != NULL; p = p->p_link)
		if (p->hostname != NULL
		    && (-1 == mode || p->hmode == mode)
		    && (AF_UNSPEC == hname_fam
			|| AF_UNSPEC == AF(&p->srcadr)
			|| hname_fam == AF(&p->srcadr))
		    && !strcasecmp(p->hostname, hostname))
			break;
	return p;
}