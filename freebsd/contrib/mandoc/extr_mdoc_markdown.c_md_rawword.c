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

/* Variables and functions */
 int ESC_EOL ; 
 int ESC_FON ; 
 int ESC_HYP ; 
 int ESC_SQU ; 
 int /*<<< orphan*/  code_blocks ; 
 int escflags ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_char (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_preword () ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
md_rawword(const char *s)
{
	md_preword();

	if (*s == '\0')
		return;

	if (escflags & ESC_FON) {
		escflags &= ~ESC_FON;
		if (*s == '*' && !code_blocks)
			fputs("&zwnj;", stdout);
	}

	while (*s != '\0') {
		switch(*s) {
		case '*':
			if (s[1] == '\0')
				escflags |= ESC_FON;
			break;
		case '[':
			escflags |= ESC_SQU;
			break;
		case ']':
			escflags |= ESC_HYP;
			escflags &= ~ESC_SQU;
			break;
		default:
			break;
		}
		md_char(*s++);
	}
	if (s[-1] == ' ')
		escflags |= ESC_EOL;
	else
		escflags &= ~ESC_EOL;
}