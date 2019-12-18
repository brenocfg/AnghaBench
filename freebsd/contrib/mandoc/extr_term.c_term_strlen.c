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
struct termp {size_t (* width ) (struct termp const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  enc; int /*<<< orphan*/  type; } ;
typedef  enum mandoc_esc { ____Placeholder_mandoc_esc } mandoc_esc ;

/* Variables and functions */
#define  ASCII_BREAK 137 
#define  ASCII_HYPH 136 
#define  ASCII_NBRSP 135 
#define  ESCAPE_DEVICE 134 
#define  ESCAPE_NUMBERED 133 
#define  ESCAPE_OVERSTRIKE 132 
#define  ESCAPE_SKIPCHAR 131 
#define  ESCAPE_SPECIAL 130 
#define  ESCAPE_UNDEF 129 
#define  ESCAPE_UNICODE 128 
 int /*<<< orphan*/  TERMENC_ASCII ; 
 int /*<<< orphan*/  TERMTYPE_PDF ; 
 int /*<<< orphan*/  TERMTYPE_PS ; 
 char* ascii_uc2str (int) ; 
 scalar_t__ cond_width (struct termp const*,char,int*) ; 
 int mandoc_escape (char const**,char const**,int*) ; 
 int mchars_num2char (char const*,int) ; 
 int mchars_num2uc (char const*,int) ; 
 int mchars_spec2cp (char const*,int) ; 
 char* mchars_spec2str (char const*,int,size_t*) ; 
 size_t strcspn (char const*,char const*) ; 
 size_t strlen (char const*) ; 
 size_t stub1 (struct termp const*,int /*<<< orphan*/ ) ; 
 size_t stub2 (struct termp const*,int /*<<< orphan*/ ) ; 

size_t
term_strlen(const struct termp *p, const char *cp)
{
	size_t		 sz, rsz, i;
	int		 ssz, skip, uc;
	const char	*seq, *rhs;
	enum mandoc_esc	 esc;
	static const char rej[] = { '\\', ASCII_NBRSP, ASCII_HYPH,
			ASCII_BREAK, '\0' };

	/*
	 * Account for escaped sequences within string length
	 * calculations.  This follows the logic in term_word() as we
	 * must calculate the width of produced strings.
	 */

	sz = 0;
	skip = 0;
	while ('\0' != *cp) {
		rsz = strcspn(cp, rej);
		for (i = 0; i < rsz; i++)
			sz += cond_width(p, *cp++, &skip);

		switch (*cp) {
		case '\\':
			cp++;
			rhs = NULL;
			esc = mandoc_escape(&cp, &seq, &ssz);
			switch (esc) {
			case ESCAPE_UNICODE:
				uc = mchars_num2uc(seq + 1, ssz - 1);
				break;
			case ESCAPE_NUMBERED:
				uc = mchars_num2char(seq, ssz);
				if (uc < 0)
					continue;
				break;
			case ESCAPE_SPECIAL:
				if (p->enc == TERMENC_ASCII) {
					rhs = mchars_spec2str(seq, ssz, &rsz);
					if (rhs != NULL)
						break;
				} else {
					uc = mchars_spec2cp(seq, ssz);
					if (uc > 0)
						sz += cond_width(p, uc, &skip);
				}
				continue;
			case ESCAPE_UNDEF:
				uc = *seq;
				break;
			case ESCAPE_DEVICE:
				if (p->type == TERMTYPE_PDF) {
					rhs = "pdf";
					rsz = 3;
				} else if (p->type == TERMTYPE_PS) {
					rhs = "ps";
					rsz = 2;
				} else if (p->enc == TERMENC_ASCII) {
					rhs = "ascii";
					rsz = 5;
				} else {
					rhs = "utf8";
					rsz = 4;
				}
				break;
			case ESCAPE_SKIPCHAR:
				skip = 1;
				continue;
			case ESCAPE_OVERSTRIKE:
				rsz = 0;
				rhs = seq + ssz;
				while (seq < rhs) {
					if (*seq == '\\') {
						mandoc_escape(&seq, NULL, NULL);
						continue;
					}
					i = (*p->width)(p, *seq++);
					if (rsz < i)
						rsz = i;
				}
				sz += rsz;
				continue;
			default:
				continue;
			}

			/*
			 * Common handling for Unicode and numbered
			 * character escape sequences.
			 */

			if (rhs == NULL) {
				if (p->enc == TERMENC_ASCII) {
					rhs = ascii_uc2str(uc);
					rsz = strlen(rhs);
				} else {
					if ((uc < 0x20 && uc != 0x09) ||
					    (uc > 0x7E && uc < 0xA0))
						uc = 0xFFFD;
					sz += cond_width(p, uc, &skip);
					continue;
				}
			}

			if (skip) {
				skip = 0;
				break;
			}

			/*
			 * Common handling for all escape sequences
			 * printing more than one character.
			 */

			for (i = 0; i < rsz; i++)
				sz += (*p->width)(p, *rhs++);
			break;
		case ASCII_NBRSP:
			sz += cond_width(p, ' ', &skip);
			cp++;
			break;
		case ASCII_HYPH:
			sz += cond_width(p, '-', &skip);
			cp++;
			break;
		default:
			break;
		}
	}

	return sz;
}