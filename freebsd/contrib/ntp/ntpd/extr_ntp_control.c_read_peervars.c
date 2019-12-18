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
typedef  int u_int ;
typedef  int u_char ;
struct peer {scalar_t__ num_events; } ;
struct ctl_var {int flags; size_t code; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CERR_BADASSOC ; 
 int /*<<< orphan*/  CERR_UNKNOWNVAR ; 
 size_t COUNTOF (int*) ; 
 int /*<<< orphan*/  CP_MAXCODE ; 
 int EOV ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  ZERO (int*) ; 
 int /*<<< orphan*/  ctl_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_flushpkt (int /*<<< orphan*/ ) ; 
 struct ctl_var* ctl_getitem (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  ctl_putpeer (int,struct peer*) ; 
 int /*<<< orphan*/  ctlpeerstatus (struct peer*) ; 
 int* def_peer_var ; 
 struct peer* findpeerbyassoc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peer_var ; 
 int /*<<< orphan*/  res_associd ; 
 scalar_t__ res_authokay ; 
 TYPE_1__ rpkt ; 

__attribute__((used)) static void
read_peervars(void)
{
	const struct ctl_var *v;
	struct peer *peer;
	const u_char *cp;
	size_t i;
	char *	valuep;
	u_char	wants[CP_MAXCODE + 1];
	u_int	gotvar;

	/*
	 * Wants info for a particular peer. See if we know
	 * the guy.
	 */
	peer = findpeerbyassoc(res_associd);
	if (NULL == peer) {
		ctl_error(CERR_BADASSOC);
		return;
	}
	rpkt.status = htons(ctlpeerstatus(peer));
	if (res_authokay)
		peer->num_events = 0;
	ZERO(wants);
	gotvar = 0;
	while (NULL != (v = ctl_getitem(peer_var, &valuep))) {
		if (v->flags & EOV) {
			ctl_error(CERR_UNKNOWNVAR);
			return;
		}
		INSIST(v->code < COUNTOF(wants));
		wants[v->code] = 1;
		gotvar = 1;
	}
	if (gotvar) {
		for (i = 1; i < COUNTOF(wants); i++)
			if (wants[i])
				ctl_putpeer(i, peer);
	} else
		for (cp = def_peer_var; *cp != 0; cp++)
			ctl_putpeer((int)*cp, peer);
	ctl_flushpkt(0);
}