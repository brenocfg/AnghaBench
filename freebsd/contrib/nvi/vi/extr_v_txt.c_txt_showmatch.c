#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_16__ ;

/* Type definitions */
struct TYPE_23__ {scalar_t__ cs_lno; scalar_t__ cs_cno; int cs_ch; scalar_t__ cs_flags; } ;
typedef  TYPE_1__ VCS ;
struct TYPE_26__ {scalar_t__ lno; scalar_t__ cno; } ;
struct TYPE_25__ {scalar_t__ lno; scalar_t__ cno; int /*<<< orphan*/ * gp; } ;
struct TYPE_24__ {scalar_t__ lno; scalar_t__ cno; } ;
struct TYPE_22__ {int /*<<< orphan*/  mcs; } ;
typedef  TYPE_2__ TEXT ;
typedef  TYPE_3__ SCR ;
typedef  TYPE_4__ MARK ;
typedef  int /*<<< orphan*/  GS ;

/* Variables and functions */
 scalar_t__ CS_EOF ; 
 scalar_t__ CS_SOF ; 
 int /*<<< orphan*/  EC_TIMEOUT ; 
 int /*<<< orphan*/  KEY_NAME (TYPE_3__*,int) ; 
 int /*<<< orphan*/  M_BERR ; 
 int /*<<< orphan*/  O_MATCHTIME ; 
 int O_VAL (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_TOP ; 
 int* STRCHR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UPDATE_POSITION (TYPE_3__*,TYPE_2__*) ; 
 TYPE_16__* VIP (TYPE_3__*) ; 
 scalar_t__ cs_init (TYPE_3__*,TYPE_1__*) ; 
 scalar_t__ cs_prev (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  msgq (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int v_event_get (TYPE_3__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ vs_refresh (TYPE_3__*,int) ; 
 scalar_t__ vs_sm_position (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
txt_showmatch(SCR *sp, TEXT *tp)
{
	GS *gp;
	VCS cs;
	MARK m;
	int cnt, endc, startc;

	gp = sp->gp;

	/*
	 * Do a refresh first, in case we haven't done one in awhile,
	 * so the user can see what we're complaining about.
	 */
	UPDATE_POSITION(sp, tp);
	if (vs_refresh(sp, 1))
		return (1);

	/*
	 * We don't display the match if it's not on the screen.  Find
	 * out what the first character on the screen is.
	 */
	if (vs_sm_position(sp, &m, 0, P_TOP))
		return (1);

	/* Initialize the getc() interface. */
	cs.cs_lno = tp->lno;
	cs.cs_cno = tp->cno - 1;
	if (cs_init(sp, &cs))
		return (1);
	startc = STRCHR(VIP(sp)->mcs, endc = cs.cs_ch)[-1];

	/* Search for the match. */
	for (cnt = 1;;) {
		if (cs_prev(sp, &cs))
			return (1);
		if (cs.cs_flags != 0) {
			if (cs.cs_flags == CS_EOF || cs.cs_flags == CS_SOF) {
				msgq(sp, M_BERR,
				    "Unmatched %s", KEY_NAME(sp, endc));
				return (0);
			}
			continue;
		}
		if (cs.cs_ch == endc)
			++cnt;
		else if (cs.cs_ch == startc && --cnt == 0)
			break;
	}

	/* If the match is on the screen, move to it. */
	if (cs.cs_lno < m.lno || (cs.cs_lno == m.lno && cs.cs_cno < m.cno))
		return (0);
	sp->lno = cs.cs_lno;
	sp->cno = cs.cs_cno;
	if (vs_refresh(sp, 1))
		return (1);

	/* Wait for timeout or character arrival. */
	return (v_event_get(sp,
	    NULL, O_VAL(sp, O_MATCHTIME) * 100, EC_TIMEOUT));
}