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
struct html {int flags; } ;
typedef  int /*<<< orphan*/  numbuf ;
typedef  enum mandoc_esc { ____Placeholder_mandoc_esc } mandoc_esc ;

/* Variables and functions */
#define  ASCII_BREAK 147 
#define  ASCII_HYPH 146 
#define  ASCII_NBRSP 145 
#define  ESCAPE_BREAK 144 
#define  ESCAPE_DEVICE 143 
#define  ESCAPE_ERROR 142 
#define  ESCAPE_FONT 141 
#define  ESCAPE_FONTBI 140 
#define  ESCAPE_FONTBOLD 139 
#define  ESCAPE_FONTCW 138 
#define  ESCAPE_FONTITALIC 137 
#define  ESCAPE_FONTPREV 136 
#define  ESCAPE_FONTROMAN 135 
#define  ESCAPE_NOSPACE 134 
#define  ESCAPE_NUMBERED 133 
#define  ESCAPE_OVERSTRIKE 132 
#define  ESCAPE_SKIPCHAR 131 
#define  ESCAPE_SPECIAL 130 
#define  ESCAPE_UNDEF 129 
#define  ESCAPE_UNICODE 128 
 int HTML_NOSPACE ; 
 int HTML_SKIPCHAR ; 
 int /*<<< orphan*/  TAG_BR ; 
 int /*<<< orphan*/  html_setfont (struct html*,int) ; 
 int mandoc_escape (char const**,char const**,int*) ; 
 int mchars_num2char (char const*,int) ; 
 int mchars_num2uc (char const*,int) ; 
 int mchars_spec2cp (char const*,int) ; 
 int /*<<< orphan*/  print_byte (struct html*,char const) ; 
 int /*<<< orphan*/  print_endword (struct html*) ; 
 scalar_t__ print_escape (struct html*,int) ; 
 int /*<<< orphan*/  print_metaf (struct html*) ; 
 int /*<<< orphan*/  print_otag (struct html*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_word (struct html*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 char* strchr (char const*,char) ; 
 size_t strcspn (char const*,char const*) ; 

__attribute__((used)) static int
print_encode(struct html *h, const char *p, const char *pend, int norecurse)
{
	char		 numbuf[16];
	const char	*seq;
	size_t		 sz;
	int		 c, len, breakline, nospace;
	enum mandoc_esc	 esc;
	static const char rejs[10] = { ' ', '\\', '<', '>', '&', '"',
		ASCII_NBRSP, ASCII_HYPH, ASCII_BREAK, '\0' };

	if (pend == NULL)
		pend = strchr(p, '\0');

	breakline = 0;
	nospace = 0;

	while (p < pend) {
		if (HTML_SKIPCHAR & h->flags && '\\' != *p) {
			h->flags &= ~HTML_SKIPCHAR;
			p++;
			continue;
		}

		for (sz = strcspn(p, rejs); sz-- && p < pend; p++)
			print_byte(h, *p);

		if (breakline &&
		    (p >= pend || *p == ' ' || *p == ASCII_NBRSP)) {
			print_otag(h, TAG_BR, "");
			breakline = 0;
			while (p < pend && (*p == ' ' || *p == ASCII_NBRSP))
				p++;
			continue;
		}

		if (p >= pend)
			break;

		if (*p == ' ') {
			print_endword(h);
			p++;
			continue;
		}

		if (print_escape(h, *p++))
			continue;

		esc = mandoc_escape(&p, &seq, &len);
		switch (esc) {
		case ESCAPE_FONT:
		case ESCAPE_FONTPREV:
		case ESCAPE_FONTBOLD:
		case ESCAPE_FONTITALIC:
		case ESCAPE_FONTBI:
		case ESCAPE_FONTCW:
		case ESCAPE_FONTROMAN:
			if (0 == norecurse) {
				h->flags |= HTML_NOSPACE;
				if (html_setfont(h, esc))
					print_metaf(h);
				h->flags &= ~HTML_NOSPACE;
			}
			continue;
		case ESCAPE_SKIPCHAR:
			h->flags |= HTML_SKIPCHAR;
			continue;
		case ESCAPE_ERROR:
			continue;
		default:
			break;
		}

		if (h->flags & HTML_SKIPCHAR) {
			h->flags &= ~HTML_SKIPCHAR;
			continue;
		}

		switch (esc) {
		case ESCAPE_UNICODE:
			/* Skip past "u" header. */
			c = mchars_num2uc(seq + 1, len - 1);
			break;
		case ESCAPE_NUMBERED:
			c = mchars_num2char(seq, len);
			if (c < 0)
				continue;
			break;
		case ESCAPE_SPECIAL:
			c = mchars_spec2cp(seq, len);
			if (c <= 0)
				continue;
			break;
		case ESCAPE_UNDEF:
			c = *seq;
			break;
		case ESCAPE_DEVICE:
			print_word(h, "html");
			continue;
		case ESCAPE_BREAK:
			breakline = 1;
			continue;
		case ESCAPE_NOSPACE:
			if ('\0' == *p)
				nospace = 1;
			continue;
		case ESCAPE_OVERSTRIKE:
			if (len == 0)
				continue;
			c = seq[len - 1];
			break;
		default:
			continue;
		}
		if ((c < 0x20 && c != 0x09) ||
		    (c > 0x7E && c < 0xA0))
			c = 0xFFFD;
		if (c > 0x7E) {
			(void)snprintf(numbuf, sizeof(numbuf), "&#x%.4X;", c);
			print_word(h, numbuf);
		} else if (print_escape(h, c) == 0)
			print_byte(h, c);
	}

	return nospace;
}