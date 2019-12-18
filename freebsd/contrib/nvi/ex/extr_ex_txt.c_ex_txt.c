#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int carat_t ;
struct TYPE_31__ {int /*<<< orphan*/  (* scr_ex_adjust ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_32__ {int e_event; int e_value; char e_c; TYPE_3__ e_ch; } ;
struct TYPE_30__ {scalar_t__ lno; TYPE_3__* gp; } ;
struct TYPE_29__ {int lb_len; scalar_t__ len; char* lb; scalar_t__ ai; scalar_t__ lno; } ;
typedef  int /*<<< orphan*/  TEXTH ;
typedef  TYPE_1__ TEXT ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_3__ GS ;
typedef  TYPE_4__ EVENT ;
typedef  int /*<<< orphan*/  ARG_CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  BINC_GOTOW (TYPE_2__*,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  CH_MAPPED ; 
#define  C_CARATSET 141 
#define  C_NOTSET 140 
#define  C_ZEROSET 139 
 int /*<<< orphan*/  EX_TERM_CE ; 
#define  E_CHARACTER 138 
#define  E_EOF 137 
#define  E_ERR 136 
#define  E_INTERRUPT 135 
#define  E_REPAINT 134 
#define  E_WRESIZE 133 
 scalar_t__ F_ISSET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_SCRIPTED ; 
 int /*<<< orphan*/  ISCNTRL (char) ; 
#define  K_CARAT 132 
#define  K_CNTRLD 131 
#define  K_CR 130 
 int K_FORMFEED ; 
#define  K_NL 129 
 int K_TAB ; 
#define  K_ZERO 128 
 int /*<<< orphan*/  LF_CLR (int /*<<< orphan*/ ) ; 
 scalar_t__ LF_ISSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LF_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMCPY (char*,char*,scalar_t__) ; 
 scalar_t__ OOBLNO ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXT_AUTOINDENT ; 
 int /*<<< orphan*/  TXT_BACKSLASH ; 
 int /*<<< orphan*/  TXT_BEAUTIFY ; 
 int /*<<< orphan*/  TXT_CNTRLD ; 
 int /*<<< orphan*/  TXT_CR ; 
 int /*<<< orphan*/  TXT_DOTTERM ; 
 int /*<<< orphan*/  TXT_EOFCHAR ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  isblank (char) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  q ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  text_free (TYPE_1__*) ; 
 TYPE_1__* text_init (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  text_lfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txt_dent (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  txt_prompt (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v_event_err (TYPE_2__*,TYPE_4__*) ; 
 scalar_t__ v_event_get (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ v_txt_auto (TYPE_2__*,scalar_t__,TYPE_1__*,scalar_t__,TYPE_1__*) ; 

int
ex_txt(SCR *sp, TEXTH *tiqh, ARG_CHAR_T prompt, u_int32_t flags)
{
	EVENT ev;
	GS *gp;
	TEXT ait, *ntp, *tp;
	carat_t carat_st;
	size_t cnt;
	int rval;
	int nochange;

	rval = 0;

	/*
	 * Get a TEXT structure with some initial buffer space, reusing the
	 * last one if it's big enough.  (All TEXT bookkeeping fields default
	 * to 0 -- text_init() handles this.)
	 */
	if (!TAILQ_EMPTY(tiqh)) {
		tp = TAILQ_FIRST(tiqh);
		if (TAILQ_NEXT(tp, q) != NULL || tp->lb_len < 32) {
			text_lfree(tiqh);
			goto newtp;
		}
		tp->len = 0;
	} else {
newtp:		if ((tp = text_init(sp, NULL, 0, 32)) == NULL)
			goto err;
		TAILQ_INSERT_HEAD(tiqh, tp, q);
	}

	/* Set the starting line number. */
	tp->lno = sp->lno + 1;

	/*
	 * If it's a terminal, set up autoindent, put out the prompt, and
	 * set it up so we know we were suspended.  Otherwise, turn off
	 * the autoindent flag, as that requires less special casing below.
	 *
	 * XXX
	 * Historic practice is that ^Z suspended command mode (but, because
	 * it ran in cooked mode, it was unaffected by the autowrite option.)
	 * On restart, any "current" input was discarded, whether in insert
	 * mode or not, and ex was in command mode.  This code matches historic
	 * practice, but not 'cause it's easier.
	 */
	gp = sp->gp;
	if (F_ISSET(gp, G_SCRIPTED))
		LF_CLR(TXT_AUTOINDENT);
	else {
		if (LF_ISSET(TXT_AUTOINDENT)) {
			LF_SET(TXT_EOFCHAR);
			if (v_txt_auto(sp, sp->lno, NULL, 0, tp))
				goto err;
		}
		txt_prompt(sp, tp, prompt, flags);
	}

	for (carat_st = C_NOTSET, nochange = 0;;) {
		if (v_event_get(sp, &ev, 0, 0))
			goto err;

		/* Deal with all non-character events. */
		switch (ev.e_event) {
		case E_CHARACTER:
			break;
		case E_ERR:
			goto err;
		case E_REPAINT:
		case E_WRESIZE:
			continue;
		case E_EOF:
			rval = 1;
			/* FALLTHROUGH */
		case E_INTERRUPT:
			/*
			 * Handle EOF/SIGINT events by discarding partially
			 * entered text and returning.  EOF returns failure,
			 * E_INTERRUPT returns success.
			 */
			goto notlast;
		default:
			v_event_err(sp, &ev);
			goto notlast;
		}

		/*
		 * Deal with character events.
		 *
		 * Check to see if the character fits into the input buffer.
		 * (Use tp->len, ignore overwrite and non-printable chars.)
		 */
		BINC_GOTOW(sp, tp->lb, tp->lb_len, tp->len + 1);

		switch (ev.e_value) {
		case K_CR:
			/*
			 * !!!
			 * Historically, <carriage-return>'s in the command
			 * weren't special, so the ex parser would return an
			 * unknown command error message.  However, if they
			 * terminated the command if they were in a map.  I'm
			 * pretty sure this still isn't right, but it handles
			 * what I've seen so far.
			 */
			if (!F_ISSET(&ev.e_ch, CH_MAPPED))
				goto ins_ch;
			/* FALLTHROUGH */
		case K_NL:
			/*
			 * '\' can escape <carriage-return>/<newline>.  We
			 * don't discard the backslash because we need it
			 * to get the <newline> through the ex parser.
			 */
			if (LF_ISSET(TXT_BACKSLASH) &&
			    tp->len != 0 && tp->lb[tp->len - 1] == '\\')
				goto ins_ch;

			/*
			 * CR returns from the ex command line.
			 *
			 * XXX
			 * Terminate with a nul, needed by filter.
			 */
			if (LF_ISSET(TXT_CR)) {
				tp->lb[tp->len] = '\0';
				goto done;
			}

			/*
			 * '.' may terminate text input mode; free the current
			 * TEXT.
			 */
			if (LF_ISSET(TXT_DOTTERM) && tp->len == tp->ai + 1 &&
			    tp->lb[tp->len - 1] == '.') {
notlast:			TAILQ_REMOVE(tiqh, tp, q);
				text_free(tp);
				goto done;
			}

			/* Set up bookkeeping for the new line. */
			if ((ntp = text_init(sp, NULL, 0, 32)) == NULL)
				goto err;
			ntp->lno = tp->lno + 1;

			/*
			 * Reset the autoindent line value.  0^D keeps the ai
			 * line from changing, ^D changes the level, even if
			 * there were no characters in the old line.  Note, if
			 * using the current tp structure, use the cursor as
			 * the length, the autoindent characters may have been
			 * erased.
			 */
			if (LF_ISSET(TXT_AUTOINDENT)) {
				if (nochange) {
					nochange = 0;
					if (v_txt_auto(sp,
					    OOBLNO, &ait, ait.ai, ntp))
						goto err;
					free(ait.lb);
				} else
					if (v_txt_auto(sp,
					    OOBLNO, tp, tp->len, ntp))
						goto err;
				carat_st = C_NOTSET;
			}
			txt_prompt(sp, ntp, prompt, flags);

			/*
			 * Swap old and new TEXT's, and insert the new TEXT
			 * into the queue.
			 */
			tp = ntp;
			TAILQ_INSERT_TAIL(tiqh, tp, q);
			break;
		case K_CARAT:			/* Delete autoindent chars. */
			if (tp->len <= tp->ai && LF_ISSET(TXT_AUTOINDENT))
				carat_st = C_CARATSET;
			goto ins_ch;
		case K_ZERO:			/* Delete autoindent chars. */
			if (tp->len <= tp->ai && LF_ISSET(TXT_AUTOINDENT))
				carat_st = C_ZEROSET;
			goto ins_ch;
		case K_CNTRLD:			/* Delete autoindent char. */
			/*
			 * !!!
			 * Historically, the ^D command took (but then ignored)
			 * a count.  For simplicity, we don't return it unless
			 * it's the first character entered.  The check for len
			 * equal to 0 is okay, TXT_AUTOINDENT won't be set.
			 */
			if (LF_ISSET(TXT_CNTRLD)) {
				for (cnt = 0; cnt < tp->len; ++cnt)
					if (!isblank(tp->lb[cnt]))
						break;
				if (cnt == tp->len) {
					tp->len = 1;
					tp->lb[0] = ev.e_c;
					tp->lb[1] = '\0';

					/*
					 * Put out a line separator, in case
					 * the command fails.
					 */
					(void)putchar('\n');
					goto done;
				}
			}

			/*
			 * POSIX 1003.1b-1993, paragraph 7.1.1.9, states that
			 * the EOF characters are discarded if there are other
			 * characters to process in the line, i.e. if the EOF
			 * is not the first character in the line.  For this
			 * reason, historic ex discarded the EOF characters,
			 * even if occurring in the middle of the input line.
			 * We match that historic practice.
			 *
			 * !!!
			 * The test for discarding in the middle of the line is
			 * done in the switch, because the CARAT forms are N+1,
			 * not N.
			 *
			 * !!!
			 * There's considerable magic to make the terminal code
			 * return the EOF character at all.  See that code for
			 * details.
			 */
			if (!LF_ISSET(TXT_AUTOINDENT) || tp->len == 0)
				continue;
			switch (carat_st) {
			case C_CARATSET:		/* ^^D */
				if (tp->len > tp->ai + 1)
					continue;

				/* Save the ai string for later. */
				ait.lb = NULL;
				ait.lb_len = 0;
				BINC_GOTOW(sp, ait.lb, ait.lb_len, tp->ai);
				MEMCPY(ait.lb, tp->lb, tp->ai);
				ait.ai = ait.len = tp->ai;

				carat_st = C_NOTSET;
				nochange = 1;
				goto leftmargin;
			case C_ZEROSET:			/* 0^D */
				if (tp->len > tp->ai + 1)
					continue;

				carat_st = C_NOTSET;
leftmargin:			(void)gp->scr_ex_adjust(sp, EX_TERM_CE);
				tp->ai = tp->len = 0;
				break;
			case C_NOTSET:			/* ^D */
				if (tp->len > tp->ai)
					continue;

				if (txt_dent(sp, tp))
					goto err;
				break;
			default:
				abort();
			}

			/* Clear and redisplay the line. */
			(void)gp->scr_ex_adjust(sp, EX_TERM_CE);
			txt_prompt(sp, tp, prompt, flags);
			break;
		default:
			/*
			 * See the TXT_BEAUTIFY comment in vi/v_txt_ev.c.
			 *
			 * Silently eliminate any iscntrl() character that was
			 * not already handled specially, except for <tab> and
			 * <ff>.
			 */
ins_ch:			if (LF_ISSET(TXT_BEAUTIFY) && ISCNTRL(ev.e_c) &&
			    ev.e_value != K_FORMFEED && ev.e_value != K_TAB)
				break;

			tp->lb[tp->len++] = ev.e_c;
			break;
		}
	}
	/* NOTREACHED */

done:	return (rval);

err:	
alloc_err:
	return (1);
}