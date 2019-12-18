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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  VICMD ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 scalar_t__ F_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LF_SET (int) ; 
 int /*<<< orphan*/  MAPPED_KEYS_WAITING (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  O_ALTWERASE ; 
 int /*<<< orphan*/  O_AUTOINDENT ; 
 int /*<<< orphan*/  O_BEAUTIFY ; 
 scalar_t__ O_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_SHOWMATCH ; 
 int /*<<< orphan*/  O_TTYWERASE ; 
 int /*<<< orphan*/  O_WRAPLEN ; 
 int /*<<< orphan*/  O_WRAPMARGIN ; 
 int /*<<< orphan*/  SC_SCRIPT ; 
 int TXT_ALTWERASE ; 
 int TXT_AUTOINDENT ; 
 int TXT_BEAUTIFY ; 
 int TXT_CNTRLT ; 
 int TXT_CR ; 
 int TXT_ESCAPE ; 
 int TXT_MAPINPUT ; 
 int TXT_RECORD ; 
 int TXT_REPLAY ; 
 int TXT_RESOLVE ; 
 int TXT_SHOWMATCH ; 
 int TXT_TTYWERASE ; 
 int TXT_WRAPMARGIN ; 
 int /*<<< orphan*/  VC_C1SET ; 
 int /*<<< orphan*/  VC_ISDOT ; 

__attribute__((used)) static u_int32_t
set_txt_std(SCR *sp, VICMD *vp, u_int32_t flags)
{
	LF_SET(TXT_CNTRLT |
	    TXT_ESCAPE | TXT_MAPINPUT | TXT_RECORD | TXT_RESOLVE);

	if (F_ISSET(vp, VC_ISDOT))
		LF_SET(TXT_REPLAY);

	if (O_ISSET(sp, O_ALTWERASE))
		LF_SET(TXT_ALTWERASE);
	if (O_ISSET(sp, O_AUTOINDENT))
		LF_SET(TXT_AUTOINDENT);
	if (O_ISSET(sp, O_BEAUTIFY))
		LF_SET(TXT_BEAUTIFY);
	if (O_ISSET(sp, O_SHOWMATCH))
		LF_SET(TXT_SHOWMATCH);
	if (F_ISSET(sp, SC_SCRIPT))
		LF_SET(TXT_CR);
	if (O_ISSET(sp, O_TTYWERASE))
		LF_SET(TXT_TTYWERASE);

	/*
	 * !!!
	 * Mapped keys were sometimes unaffected by the wrapmargin option
	 * in the historic 4BSD vi.  Consider the following commands, where
	 * each is executed on an empty line, in an 80 column screen, with
	 * the wrapmargin value set to 60.
	 *
	 *	aABC DEF <ESC>....
	 *	:map K aABC DEF ^V<ESC><CR>KKKKK
	 *	:map K 5aABC DEF ^V<ESC><CR>K
	 *
	 * The first and second commands are affected by wrapmargin.  The
	 * third is not.  (If the inserted text is itself longer than the
	 * wrapmargin value, i.e. if the "ABC DEF " string is replaced by
	 * something that's longer than 60 columns from the beginning of
	 * the line, the first two commands behave as before, but the third
	 * command gets fairly strange.)  The problem is that people wrote
	 * macros that depended on the third command NOT being affected by
	 * wrapmargin, as in this gem which centers lines:
	 *
	 *	map #c $mq81a ^V^[81^V^V|D`qld0:s/  / /g^V^M$p
	 *
	 * For compatibility reasons, we try and make it all work here.  I
	 * offer no hope that this is right, but it's probably pretty close.
	 *
	 * XXX
	 * Once I work my courage up, this is all gonna go away.  It's too
	 * evil to survive.
	 */
	if ((O_ISSET(sp, O_WRAPLEN) || O_ISSET(sp, O_WRAPMARGIN)) &&
	    (!MAPPED_KEYS_WAITING(sp) || !F_ISSET(vp, VC_C1SET)))
		LF_SET(TXT_WRAPMARGIN);
	return (flags);
}