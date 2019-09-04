#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct grep_pat {scalar_t__ token; size_t field; scalar_t__ word_regexp; } ;
struct TYPE_6__ {int rm_so; int rm_eo; } ;
typedef  TYPE_1__ regmatch_t ;
typedef  enum grep_context { ____Placeholder_grep_context } grep_context ;
struct TYPE_7__ {char* field; size_t len; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_4__*) ; 
 int GREP_CONTEXT_HEAD ; 
#define  GREP_HEADER_AUTHOR 129 
#define  GREP_HEADER_COMMITTER 128 
 scalar_t__ GREP_PATTERN ; 
 scalar_t__ GREP_PATTERN_HEAD ; 
 int REG_NOTBOL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  die (char*) ; 
 TYPE_4__* header_field ; 
 int patmatch (struct grep_pat*,char*,char*,TYPE_1__*,int) ; 
 int strip_timestamp (char*,char**) ; 
 scalar_t__ strncmp (char*,char const*,size_t) ; 
 scalar_t__ word_char (char) ; 

__attribute__((used)) static int match_one_pattern(struct grep_pat *p, char *bol, char *eol,
			     enum grep_context ctx,
			     regmatch_t *pmatch, int eflags)
{
	int hit = 0;
	int saved_ch = 0;
	const char *start = bol;

	if ((p->token != GREP_PATTERN) &&
	    ((p->token == GREP_PATTERN_HEAD) != (ctx == GREP_CONTEXT_HEAD)))
		return 0;

	if (p->token == GREP_PATTERN_HEAD) {
		const char *field;
		size_t len;
		assert(p->field < ARRAY_SIZE(header_field));
		field = header_field[p->field].field;
		len = header_field[p->field].len;
		if (strncmp(bol, field, len))
			return 0;
		bol += len;
		switch (p->field) {
		case GREP_HEADER_AUTHOR:
		case GREP_HEADER_COMMITTER:
			saved_ch = strip_timestamp(bol, &eol);
			break;
		default:
			break;
		}
	}

 again:
	hit = patmatch(p, bol, eol, pmatch, eflags);

	if (hit && p->word_regexp) {
		if ((pmatch[0].rm_so < 0) ||
		    (eol - bol) < pmatch[0].rm_so ||
		    (pmatch[0].rm_eo < 0) ||
		    (eol - bol) < pmatch[0].rm_eo)
			die("regexp returned nonsense");

		/* Match beginning must be either beginning of the
		 * line, or at word boundary (i.e. the last char must
		 * not be a word char).  Similarly, match end must be
		 * either end of the line, or at word boundary
		 * (i.e. the next char must not be a word char).
		 */
		if ( ((pmatch[0].rm_so == 0) ||
		      !word_char(bol[pmatch[0].rm_so-1])) &&
		     ((pmatch[0].rm_eo == (eol-bol)) ||
		      !word_char(bol[pmatch[0].rm_eo])) )
			;
		else
			hit = 0;

		/* Words consist of at least one character. */
		if (pmatch->rm_so == pmatch->rm_eo)
			hit = 0;

		if (!hit && pmatch[0].rm_so + bol + 1 < eol) {
			/* There could be more than one match on the
			 * line, and the first match might not be
			 * strict word match.  But later ones could be!
			 * Forward to the next possible start, i.e. the
			 * next position following a non-word char.
			 */
			bol = pmatch[0].rm_so + bol + 1;
			while (word_char(bol[-1]) && bol < eol)
				bol++;
			eflags |= REG_NOTBOL;
			if (bol < eol)
				goto again;
		}
	}
	if (p->token == GREP_PATTERN_HEAD && saved_ch)
		*eol = saved_ch;
	if (hit) {
		pmatch[0].rm_so += bol - start;
		pmatch[0].rm_eo += bol - start;
	}
	return hit;
}