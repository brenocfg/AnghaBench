#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VI_PRIVATE ;
struct TYPE_6__ {int olen; int /*<<< orphan*/ * output; } ;
struct TYPE_5__ {int cno; int offset; size_t ai; int owrite; int /*<<< orphan*/  len; int /*<<< orphan*/  insert; int /*<<< orphan*/ * lb; } ;
typedef  TYPE_1__ TEXT ;
typedef  TYPE_2__ SEQ ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  CH_ABBREVIATED ; 
 int /*<<< orphan*/  MEMMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEQ_ABBREV ; 
 int /*<<< orphan*/ * VIP (int /*<<< orphan*/ *) ; 
 scalar_t__ ex_is_abbrev (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ inword (int /*<<< orphan*/ ) ; 
 scalar_t__ isblank (int /*<<< orphan*/ ) ; 
 TYPE_2__* seq_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ v_event_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
txt_abbrev(SCR *sp, TEXT *tp, CHAR_T *pushcp, int isinfoline, int *didsubp, int *turnoffp)
{
	VI_PRIVATE *vip;
	CHAR_T ch, *p;
	SEQ *qp;
	size_t len, off;

	/* Check to make sure we're not at the start of an append. */
	*didsubp = 0;
	if (tp->cno == tp->offset)
		return (0);

	vip = VIP(sp);

	/*
	 * Find the start of the "word".
	 *
	 * !!!
	 * We match historic practice, which, as far as I can tell, had an
	 * off-by-one error.  The way this worked was that when the inserted
	 * text switched from a "word" character to a non-word character,
	 * vi would check for possible abbreviations.  It would then take the
	 * type (i.e. word/non-word) of the character entered TWO characters
	 * ago, and move backward in the text until reaching a character that
	 * was not that type, or the beginning of the insert, the line, or
	 * the file.  For example, in the string "abc<space>", when the <space>
	 * character triggered the abbreviation check, the type of the 'b'
	 * character was used for moving through the string.  Maybe there's a
	 * reason for not using the first (i.e. 'c') character, but I can't
	 * think of one.
	 *
	 * Terminate at the beginning of the insert or the character after the
	 * offset character -- both can be tested for using tp->offset.
	 */
	off = tp->cno - 1;			/* Previous character. */
	p = tp->lb + off;
	len = 1;				/* One character test. */
	if (off == tp->offset || isblank(p[-1]))
		goto search;
	if (inword(p[-1]))			/* Move backward to change. */
		for (;;) {
			--off; --p; ++len;
			if (off == tp->offset || !inword(p[-1]))
				break;
		}
	else
		for (;;) {
			--off; --p; ++len;
			if (off == tp->offset ||
			    inword(p[-1]) || isblank(p[-1]))
				break;
		}

	/*
	 * !!!
	 * Historic vi exploded abbreviations on the command line.  This has
	 * obvious problems in that unabbreviating the string can be extremely
	 * tricky, particularly if the string has, say, an embedded escape
	 * character.  Personally, I think it's a stunningly bad idea.  Other
	 * examples of problems this caused in historic vi are:
	 *	:ab foo bar
	 *	:ab foo baz
	 * results in "bar" being abbreviated to "baz", which wasn't what the
	 * user had in mind at all.  Also, the commands:
	 *	:ab foo bar
	 *	:unab foo<space>
	 * resulted in an error message that "bar" wasn't mapped.  Finally,
	 * since the string was already exploded by the time the unabbreviate
	 * command got it, all it knew was that an abbreviation had occurred.
	 * Cleverly, it checked the replacement string for its unabbreviation
	 * match, which meant that the commands:
	 *	:ab foo1 bar
	 *	:ab foo2 bar
	 *	:unab foo2
	 * unabbreviate "foo1", and the commands:
	 *	:ab foo bar
	 *	:ab bar baz
	 * unabbreviate "foo"!
	 *
	 * Anyway, people neglected to first ask my opinion before they wrote
	 * macros that depend on this stuff, so, we make this work as follows.
	 * When checking for an abbreviation on the command line, if we get a
	 * string which is <blank> terminated and which starts at the beginning
	 * of the line, we check to see it is the abbreviate or unabbreviate
	 * commands.  If it is, turn abbreviations off and return as if no
	 * abbreviation was found.  Note also, minor trickiness, so that if
	 * the user erases the line and starts another command, we turn the
	 * abbreviations back on.
	 *
	 * This makes the layering look like a Nachos Supreme.
	 */
search:	if (isinfoline)
		if (off == tp->ai || off == tp->offset)
			if (ex_is_abbrev(p, len)) {
				*turnoffp = 1;
				return (0);
			} else
				*turnoffp = 0;
		else
			if (*turnoffp)
				return (0);

	/* Check for any abbreviations. */
	if ((qp = seq_find(sp, NULL, NULL, p, len, SEQ_ABBREV, NULL)) == NULL)
		return (0);

	/*
	 * Push the abbreviation onto the tty stack.  Historically, characters
	 * resulting from an abbreviation expansion were themselves subject to
	 * map expansions, O_SHOWMATCH matching etc.  This means the expanded
	 * characters will be re-tested for abbreviations.  It's difficult to
	 * know what historic practice in this case was, since abbreviations
	 * were applied to :colon command lines, so entering abbreviations that
	 * looped was tricky, although possible.  In addition, obvious loops
	 * didn't work as expected.  (The command ':ab a b|ab b c|ab c a' will
	 * silently only implement and/or display the last abbreviation.)
	 *
	 * This implementation doesn't recover well from such abbreviations.
	 * The main input loop counts abbreviated characters, and, when it
	 * reaches a limit, discards any abbreviated characters on the queue.
	 * It's difficult to back up to the original position, as the replay
	 * queue would have to be adjusted, and the line state when an initial
	 * abbreviated character was received would have to be saved.
	 */
	ch = *pushcp;
	if (v_event_push(sp, NULL, &ch, 1, CH_ABBREVIATED))
		return (1);
	if (v_event_push(sp, NULL, qp->output, qp->olen, CH_ABBREVIATED))
		return (1);

	/*
	 * If the size of the abbreviation is larger than or equal to the size
	 * of the original text, move to the start of the replaced characters,
	 * and add their length to the overwrite count.
	 *
	 * If the abbreviation is smaller than the original text, we have to
	 * delete the additional overwrite characters and copy down any insert
	 * characters.
	 */
	tp->cno -= len;
	if (qp->olen >= len)
		tp->owrite += len;
	else {
		if (tp->insert)
			MEMMOVE(tp->lb + tp->cno + qp->olen,
			    tp->lb + tp->cno + tp->owrite + len, tp->insert);
		tp->owrite += qp->olen;
		tp->len -= len - qp->olen;
	}

	/*
	 * We return the length of the abbreviated characters.  This is so
	 * the calling routine can replace the replay characters with the
	 * abbreviation.  This means that subsequent '.' commands will produce
	 * the same text, regardless of intervening :[un]abbreviate commands.
	 * This is historic practice.
	 */
	*didsubp = len;
	return (0);
}