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
struct termp {int flags; scalar_t__ enc; int col; int ti; size_t (* width ) (struct termp*,int) ;TYPE_1__* tcol; int /*<<< orphan*/  type; scalar_t__ skipvsp; } ;
struct roffsu {int dummy; } ;
typedef  enum mandoc_esc { ____Placeholder_mandoc_esc } mandoc_esc ;
struct TYPE_2__ {size_t offset; int rmargin; int lastcol; char* buf; } ;

/* Variables and functions */
 char const ASCII_NBRSP ; 
#define  ESCAPE_BREAK 145 
#define  ESCAPE_DEVICE 144 
#define  ESCAPE_FONT 143 
#define  ESCAPE_FONTBI 142 
#define  ESCAPE_FONTBOLD 141 
#define  ESCAPE_FONTCW 140 
#define  ESCAPE_FONTITALIC 139 
#define  ESCAPE_FONTPREV 138 
#define  ESCAPE_FONTROMAN 137 
#define  ESCAPE_HLINE 136 
#define  ESCAPE_HORIZ 135 
#define  ESCAPE_NOSPACE 134 
#define  ESCAPE_NUMBERED 133 
#define  ESCAPE_OVERSTRIKE 132 
#define  ESCAPE_SKIPCHAR 131 
#define  ESCAPE_SPECIAL 130 
#define  ESCAPE_UNDEF 129 
#define  ESCAPE_UNICODE 128 
 int /*<<< orphan*/  SCALE_EM ; 
 scalar_t__ TERMENC_ASCII ; 
 int /*<<< orphan*/  TERMFONT_BI ; 
 int /*<<< orphan*/  TERMFONT_BOLD ; 
 int /*<<< orphan*/  TERMFONT_NONE ; 
 int /*<<< orphan*/  TERMFONT_UNDER ; 
 int TERMP_BACKAFTER ; 
 int TERMP_BACKBEFORE ; 
 int TERMP_KEEP ; 
 int TERMP_NBRWORD ; 
 int TERMP_NOBUF ; 
 int TERMP_NONEWLINE ; 
 int TERMP_NONOSPACE ; 
 int TERMP_NOSPACE ; 
 int TERMP_PREKEEP ; 
 int TERMP_SENTENCE ; 
 int /*<<< orphan*/  TERMTYPE_PDF ; 
 int /*<<< orphan*/  TERMTYPE_PS ; 
 char* a2roffsu (char const*,struct roffsu*,int /*<<< orphan*/ ) ; 
 char* ascii_uc2str (int) ; 
 int /*<<< orphan*/  bufferc (struct termp*,char const) ; 
 int /*<<< orphan*/  encode (struct termp*,char const*,size_t) ; 
 int /*<<< orphan*/  encode1 (struct termp*,int) ; 
 int mandoc_escape (char const**,char const**,int*) ; 
 int mchars_num2char (char const*,int) ; 
 int mchars_num2uc (char const*,int) ; 
 int mchars_spec2cp (char const*,int) ; 
 char* mchars_spec2str (char const*,int,size_t*) ; 
 size_t strcspn (char const*,char*) ; 
 size_t strlen (char const*) ; 
 size_t stub1 (struct termp*,int) ; 
 int /*<<< orphan*/  term_fontlast (struct termp*) ; 
 int /*<<< orphan*/  term_fontrepl (struct termp*,int /*<<< orphan*/ ) ; 
 int term_hen (struct termp*,struct roffsu*) ; 
 size_t term_strlen (struct termp*,char const*) ; 

void
term_word(struct termp *p, const char *word)
{
	struct roffsu	 su;
	const char	 nbrsp[2] = { ASCII_NBRSP, 0 };
	const char	*seq, *cp;
	int		 sz, uc;
	size_t		 csz, lsz, ssz;
	enum mandoc_esc	 esc;

	if ((p->flags & TERMP_NOBUF) == 0) {
		if ((p->flags & TERMP_NOSPACE) == 0) {
			if ((p->flags & TERMP_KEEP) == 0) {
				bufferc(p, ' ');
				if (p->flags & TERMP_SENTENCE)
					bufferc(p, ' ');
			} else
				bufferc(p, ASCII_NBRSP);
		}
		if (p->flags & TERMP_PREKEEP)
			p->flags |= TERMP_KEEP;
		if (p->flags & TERMP_NONOSPACE)
			p->flags |= TERMP_NOSPACE;
		else
			p->flags &= ~TERMP_NOSPACE;
		p->flags &= ~(TERMP_SENTENCE | TERMP_NONEWLINE);
		p->skipvsp = 0;
	}

	while ('\0' != *word) {
		if ('\\' != *word) {
			if (TERMP_NBRWORD & p->flags) {
				if (' ' == *word) {
					encode(p, nbrsp, 1);
					word++;
					continue;
				}
				ssz = strcspn(word, "\\ ");
			} else
				ssz = strcspn(word, "\\");
			encode(p, word, ssz);
			word += (int)ssz;
			continue;
		}

		word++;
		esc = mandoc_escape(&word, &seq, &sz);
		switch (esc) {
		case ESCAPE_UNICODE:
			uc = mchars_num2uc(seq + 1, sz - 1);
			break;
		case ESCAPE_NUMBERED:
			uc = mchars_num2char(seq, sz);
			if (uc < 0)
				continue;
			break;
		case ESCAPE_SPECIAL:
			if (p->enc == TERMENC_ASCII) {
				cp = mchars_spec2str(seq, sz, &ssz);
				if (cp != NULL)
					encode(p, cp, ssz);
			} else {
				uc = mchars_spec2cp(seq, sz);
				if (uc > 0)
					encode1(p, uc);
			}
			continue;
		case ESCAPE_UNDEF:
			uc = *seq;
			break;
		case ESCAPE_FONTBOLD:
			term_fontrepl(p, TERMFONT_BOLD);
			continue;
		case ESCAPE_FONTITALIC:
			term_fontrepl(p, TERMFONT_UNDER);
			continue;
		case ESCAPE_FONTBI:
			term_fontrepl(p, TERMFONT_BI);
			continue;
		case ESCAPE_FONT:
		case ESCAPE_FONTCW:
		case ESCAPE_FONTROMAN:
			term_fontrepl(p, TERMFONT_NONE);
			continue;
		case ESCAPE_FONTPREV:
			term_fontlast(p);
			continue;
		case ESCAPE_BREAK:
			bufferc(p, '\n');
			continue;
		case ESCAPE_NOSPACE:
			if (p->flags & TERMP_BACKAFTER)
				p->flags &= ~TERMP_BACKAFTER;
			else if (*word == '\0')
				p->flags |= (TERMP_NOSPACE | TERMP_NONEWLINE);
			continue;
		case ESCAPE_DEVICE:
			if (p->type == TERMTYPE_PDF)
				encode(p, "pdf", 3);
			else if (p->type == TERMTYPE_PS)
				encode(p, "ps", 2);
			else if (p->enc == TERMENC_ASCII)
				encode(p, "ascii", 5);
			else
				encode(p, "utf8", 4);
			continue;
		case ESCAPE_HORIZ:
			if (*seq == '|') {
				seq++;
				uc = -p->col;
			} else
				uc = 0;
			if (a2roffsu(seq, &su, SCALE_EM) == NULL)
				continue;
			uc += term_hen(p, &su);
			if (uc > 0)
				while (uc-- > 0)
					bufferc(p, ASCII_NBRSP);
			else if (p->col > (size_t)(-uc))
				p->col += uc;
			else {
				uc += p->col;
				p->col = 0;
				if (p->tcol->offset > (size_t)(-uc)) {
					p->ti += uc;
					p->tcol->offset += uc;
				} else {
					p->ti -= p->tcol->offset;
					p->tcol->offset = 0;
				}
			}
			continue;
		case ESCAPE_HLINE:
			if ((cp = a2roffsu(seq, &su, SCALE_EM)) == NULL)
				continue;
			uc = term_hen(p, &su);
			if (uc <= 0) {
				if (p->tcol->rmargin <= p->tcol->offset)
					continue;
				lsz = p->tcol->rmargin - p->tcol->offset;
			} else
				lsz = uc;
			if (*cp == seq[-1])
				uc = -1;
			else if (*cp == '\\') {
				seq = cp + 1;
				esc = mandoc_escape(&seq, &cp, &sz);
				switch (esc) {
				case ESCAPE_UNICODE:
					uc = mchars_num2uc(cp + 1, sz - 1);
					break;
				case ESCAPE_NUMBERED:
					uc = mchars_num2char(cp, sz);
					break;
				case ESCAPE_SPECIAL:
					uc = mchars_spec2cp(cp, sz);
					break;
				case ESCAPE_UNDEF:
					uc = *seq;
					break;
				default:
					uc = -1;
					break;
				}
			} else
				uc = *cp;
			if (uc < 0x20 || (uc > 0x7E && uc < 0xA0))
				uc = '_';
			if (p->enc == TERMENC_ASCII) {
				cp = ascii_uc2str(uc);
				csz = term_strlen(p, cp);
				ssz = strlen(cp);
			} else
				csz = (*p->width)(p, uc);
			while (lsz >= csz) {
				if (p->enc == TERMENC_ASCII)
					encode(p, cp, ssz);
				else
					encode1(p, uc);
				lsz -= csz;
			}
			continue;
		case ESCAPE_SKIPCHAR:
			p->flags |= TERMP_BACKAFTER;
			continue;
		case ESCAPE_OVERSTRIKE:
			cp = seq + sz;
			while (seq < cp) {
				if (*seq == '\\') {
					mandoc_escape(&seq, NULL, NULL);
					continue;
				}
				encode1(p, *seq++);
				if (seq < cp) {
					if (p->flags & TERMP_BACKBEFORE)
						p->flags |= TERMP_BACKAFTER;
					else
						p->flags |= TERMP_BACKBEFORE;
				}
			}
			/* Trim trailing backspace/blank pair. */
			if (p->tcol->lastcol > 2 &&
			    (p->tcol->buf[p->tcol->lastcol - 1] == ' ' ||
			     p->tcol->buf[p->tcol->lastcol - 1] == '\t'))
				p->tcol->lastcol -= 2;
			if (p->col > p->tcol->lastcol)
				p->col = p->tcol->lastcol;
			continue;
		default:
			continue;
		}

		/*
		 * Common handling for Unicode and numbered
		 * character escape sequences.
		 */

		if (p->enc == TERMENC_ASCII) {
			cp = ascii_uc2str(uc);
			encode(p, cp, strlen(cp));
		} else {
			if ((uc < 0x20 && uc != 0x09) ||
			    (uc > 0x7E && uc < 0xA0))
				uc = 0xFFFD;
			encode1(p, uc);
		}
	}
	p->flags &= ~TERMP_NBRWORD;
}