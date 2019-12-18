#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_3__ {int /*<<< orphan*/  state; scalar_t__* str; } ;
typedef  TYPE_1__ STR ;

/* Variables and functions */
 int /*<<< orphan*/  EOS ; 
 int /*<<< orphan*/  isdigit (int) ; 

__attribute__((used)) static int
backslash(STR *s, int *is_octal)
{
	int ch, cnt, val;

	if (is_octal != NULL)
		*is_octal = 0;
	for (cnt = val = 0;;) {
		ch = (u_char)*++s->str;
		if (!isdigit(ch) || ch > '7')
			break;
		val = val * 8 + ch - '0';
		if (++cnt == 3) {
			++s->str;
			break;
		}
	}
	if (cnt) {
		if (is_octal != NULL)
			*is_octal = 1;
		return (val);
	}
	if (ch != '\0')
		++s->str;
	switch (ch) {
		case 'a':			/* escape characters */
			return ('\7');
		case 'b':
			return ('\b');
		case 'f':
			return ('\f');
		case 'n':
			return ('\n');
		case 'r':
			return ('\r');
		case 't':
			return ('\t');
		case 'v':
			return ('\13');
		case '\0':			/*  \" -> \ */
			s->state = EOS;
			return ('\\');
		default:			/* \x" -> x */
			return (ch);
	}
}