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
typedef  int u_char ;
struct refclockstat {struct ctl_var* kv_list; } ;
struct recvbuf {int dummy; } ;
struct peer {int flags; int /*<<< orphan*/  srcadr; struct peer* p_link; } ;
struct ctl_var {int flags; size_t code; int /*<<< orphan*/  text; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int CC_MAXCODE ; 
 int /*<<< orphan*/  CERR_BADASSOC ; 
 int /*<<< orphan*/  CERR_BADVALUE ; 
 int /*<<< orphan*/  CERR_UNKNOWNVAR ; 
 int DEF ; 
 int EOV ; 
 int FALSE ; 
 int FLAG_REFCLOCK ; 
 int TRUE ; 
 struct ctl_var* clock_var ; 
 int count_var (struct ctl_var*) ; 
 int /*<<< orphan*/  ctl_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_flushpkt (int /*<<< orphan*/ ) ; 
 struct ctl_var* ctl_getitem (struct ctl_var*,char**) ; 
 int /*<<< orphan*/  ctl_putclock (int,struct refclockstat*,int) ; 
 int /*<<< orphan*/  ctl_putdata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ctlclkstatus (struct refclockstat*) ; 
 int* def_clock_var ; 
 int* emalloc_zero (size_t) ; 
 struct peer* findpeerbyassoc (scalar_t__) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  free_varlist (struct ctl_var*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct peer* peer_list ; 
 int /*<<< orphan*/  refclock_control (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct refclockstat*) ; 
 scalar_t__ res_associd ; 
 TYPE_1__ rpkt ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 struct peer* sys_peer ; 

__attribute__((used)) static void
read_clockstatus(
	struct recvbuf *rbufp,
	int restrict_mask
	)
{
#ifndef REFCLOCK
	/*
	 * If no refclock support, no data to return
	 */
	ctl_error(CERR_BADASSOC);
#else
	const struct ctl_var *	v;
	int			i;
	struct peer *		peer;
	char *			valuep;
	u_char *		wants;
	size_t			wants_alloc;
	int			gotvar;
	const u_char *		cc;
	struct ctl_var *	kv;
	struct refclockstat	cs;

	if (res_associd != 0) {
		peer = findpeerbyassoc(res_associd);
	} else {
		/*
		 * Find a clock for this jerk.	If the system peer
		 * is a clock use it, else search peer_list for one.
		 */
		if (sys_peer != NULL && (FLAG_REFCLOCK &
		    sys_peer->flags))
			peer = sys_peer;
		else
			for (peer = peer_list;
			     peer != NULL;
			     peer = peer->p_link)
				if (FLAG_REFCLOCK & peer->flags)
					break;
	}
	if (NULL == peer || !(FLAG_REFCLOCK & peer->flags)) {
		ctl_error(CERR_BADASSOC);
		return;
	}
	/*
	 * If we got here we have a peer which is a clock. Get his
	 * status.
	 */
	cs.kv_list = NULL;
	refclock_control(&peer->srcadr, NULL, &cs);
	kv = cs.kv_list;
	/*
	 * Look for variables in the packet.
	 */
	rpkt.status = htons(ctlclkstatus(&cs));
	wants_alloc = CC_MAXCODE + 1 + count_var(kv);
	wants = emalloc_zero(wants_alloc);
	gotvar = FALSE;
	while (NULL != (v = ctl_getitem(clock_var, &valuep))) {
		if (!(EOV & v->flags)) {
			wants[v->code] = TRUE;
			gotvar = TRUE;
		} else {
			v = ctl_getitem(kv, &valuep);
			if (NULL == v) {
				ctl_error(CERR_BADVALUE);
				free(wants);
				free_varlist(cs.kv_list);
				return;
			}
			if (EOV & v->flags) {
				ctl_error(CERR_UNKNOWNVAR);
				free(wants);
				free_varlist(cs.kv_list);
				return;
			}
			wants[CC_MAXCODE + 1 + v->code] = TRUE;
			gotvar = TRUE;
		}
	}

	if (gotvar) {
		for (i = 1; i <= CC_MAXCODE; i++)
			if (wants[i])
				ctl_putclock(i, &cs, TRUE);
		if (kv != NULL)
			for (i = 0; !(EOV & kv[i].flags); i++)
				if (wants[i + CC_MAXCODE + 1])
					ctl_putdata(kv[i].text,
						    strlen(kv[i].text),
						    FALSE);
	} else {
		for (cc = def_clock_var; *cc != 0; cc++)
			ctl_putclock((int)*cc, &cs, FALSE);
		for ( ; kv != NULL && !(EOV & kv->flags); kv++)
			if (DEF & kv->flags)
				ctl_putdata(kv->text, strlen(kv->text),
					    FALSE);
	}

	free(wants);
	free_varlist(cs.kv_list);

	ctl_flushpkt(0);
#endif
}