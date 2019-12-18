#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
typedef  int dir_t ;
struct TYPE_5__ {int /*<<< orphan*/  m_stop; int /*<<< orphan*/  m_final; int /*<<< orphan*/  m_start; } ;
typedef  TYPE_1__ VICMD ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
#define  BACKWARD 130 
#define  FORWARD 129 
 scalar_t__ ISMOTION (TYPE_1__*) ; 
 int /*<<< orphan*/  KEYS_WAITING (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LF_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_ERR ; 
#define  NOTSET 128 
 int /*<<< orphan*/  SEARCH_EOL ; 
 int /*<<< orphan*/  SEARCH_MSG ; 
 int /*<<< orphan*/  SEARCH_WMSG ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  b_search (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_search (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ v_correct (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
v_search(SCR *sp, VICMD *vp, CHAR_T *ptrn, size_t plen, u_int flags, dir_t dir)
{
	/* Display messages. */
	LF_SET(SEARCH_MSG);

	/* If it's a motion search, offset past end-of-line is okay. */
	if (ISMOTION(vp))
		LF_SET(SEARCH_EOL);

	/*
	 * XXX
	 * Warn if the search wraps.  See the comment above, in v_exaddr().
	 */
	if (!KEYS_WAITING(sp))
		LF_SET(SEARCH_WMSG);
		
	switch (dir) {
	case BACKWARD:
		if (b_search(sp,
		    &vp->m_start, &vp->m_stop, ptrn, plen, NULL, flags))
			return (1);
		break;
	case FORWARD:
		if (f_search(sp,
		    &vp->m_start, &vp->m_stop, ptrn, plen, NULL, flags))
			return (1);
		break;
	case NOTSET:
		msgq(sp, M_ERR, "189|No previous search pattern");
		return (1);
	default:
		abort();
	}

	/* Correct motion commands, otherwise, simply move to the location. */
	if (ISMOTION(vp)) {
		if (v_correct(sp, vp, 0))
			return(1);
	} else
		vp->m_final = vp->m_stop;
	return (0);
}