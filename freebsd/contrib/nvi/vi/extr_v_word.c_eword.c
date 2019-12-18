#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  enum which { ____Placeholder_which } which ;
struct TYPE_13__ {scalar_t__ lno; scalar_t__ cno; } ;
struct TYPE_11__ {int count; TYPE_3__ m_stop; TYPE_3__ m_start; TYPE_3__ m_final; } ;
typedef  TYPE_1__ VICMD ;
struct TYPE_12__ {scalar_t__ cs_lno; scalar_t__ cs_cno; scalar_t__ cs_flags; int /*<<< orphan*/  cs_ch; } ;
typedef  TYPE_2__ VCS ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 int BIGWORD ; 
 scalar_t__ CS_EOF ; 
 scalar_t__ F_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ISBLANK (int /*<<< orphan*/ ) ; 
 scalar_t__ ISMOTION (TYPE_1__*) ; 
 int /*<<< orphan*/  VC_C1SET ; 
 scalar_t__ cs_fblank (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ cs_init (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ cs_next (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ cs_prev (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ inword (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v_eof (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static int
eword(SCR *sp, VICMD *vp, enum which type)
{
	enum { INWORD, NOTWORD } state;
	VCS cs;
	u_long cnt;

	cnt = F_ISSET(vp, VC_C1SET) ? vp->count : 1;
	cs.cs_lno = vp->m_start.lno;
	cs.cs_cno = vp->m_start.cno;
	if (cs_init(sp, &cs))
		return (1);

	/*
	 * !!!
	 * If in whitespace, or the next character is whitespace, move past
	 * it.  (This doesn't count as a word move.)  Stay at the character
	 * past the current one, it sets word "state" for the 'e' command.
	 */
	if (cs.cs_flags == 0 && !ISBLANK(cs.cs_ch)) {
		if (cs_next(sp, &cs))
			return (1);
		if (cs.cs_flags == 0 && !ISBLANK(cs.cs_ch))
			goto start;
	}
	if (cs_fblank(sp, &cs))
		return (1);

	/*
	 * Cyclically move to the next word -- this involves skipping
	 * over word characters and then any trailing non-word characters.
	 * Note, for the 'e' command, the definition of a word keeps
	 * switching.
	 */
start:	if (type == BIGWORD)
		while (cnt--) {
			for (;;) {
				if (cs_next(sp, &cs))
					return (1);
				if (cs.cs_flags == CS_EOF)
					goto ret;
				if (cs.cs_flags != 0 || ISBLANK(cs.cs_ch))
					break;
			}
			/*
			 * When we reach the start of the word after the last
			 * word, we're done.  If we changed state, back up one
			 * to the end of the previous word.
			 */
			if (cnt == 0) {
				if (cs.cs_flags == 0 && cs_prev(sp, &cs))
					return (1);
				break;
			}

			/* Eat whitespace characters. */
			if (cs_fblank(sp, &cs))
				return (1);
			if (cs.cs_flags == CS_EOF)
				goto ret;
		}
	else
		while (cnt--) {
			state = cs.cs_flags == 0 &&
			    inword(cs.cs_ch) ? INWORD : NOTWORD;
			for (;;) {
				if (cs_next(sp, &cs))
					return (1);
				if (cs.cs_flags == CS_EOF)
					goto ret;
				if (cs.cs_flags != 0 || ISBLANK(cs.cs_ch))
					break;
				if (state == INWORD) {
					if (!inword(cs.cs_ch))
						break;
				} else
					if (inword(cs.cs_ch))
						break;
			}
			/* See comment above. */
			if (cnt == 0) {
				if (cs.cs_flags == 0 && cs_prev(sp, &cs))
					return (1);
				break;
			}

			/* Eat whitespace characters. */
			if (cs.cs_flags != 0 || ISBLANK(cs.cs_ch))
				if (cs_fblank(sp, &cs))
					return (1);
			if (cs.cs_flags == CS_EOF)
				goto ret;
		}

	/*
	 * If we didn't move, we must be at EOF.
	 *
	 * !!!
	 * That's okay for motion commands, however.
	 */
ret:	if (!ISMOTION(vp) &&
	    cs.cs_lno == vp->m_start.lno && cs.cs_cno == vp->m_start.cno) {
		v_eof(sp, &vp->m_start);
		return (1);
	}

	/* Set the end of the range for motion commands. */
	vp->m_stop.lno = cs.cs_lno;
	vp->m_stop.cno = cs.cs_cno;

	/*
	 * Non-motion commands move to the end of the range.
	 * Delete and yank stay at the start, ignore others.
	 */
	vp->m_final = ISMOTION(vp) ? vp->m_start : vp->m_stop;
	return (0);
}