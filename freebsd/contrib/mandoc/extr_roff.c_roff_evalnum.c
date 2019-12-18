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
struct roff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANDOCERR_DIVZERO ; 
 int ROFFNUM_WHITE ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int,int,char*,char const*) ; 
 int /*<<< orphan*/  roff_evalpar (struct roff*,int,char const*,int*,int*,int) ; 
 int /*<<< orphan*/  roff_getop (char const*,int*,char*) ; 

__attribute__((used)) static int
roff_evalnum(struct roff *r, int ln, const char *v,
	int *pos, int *res, int flags)
{
	int		 mypos, operand2;
	char		 operator;

	if (NULL == pos) {
		mypos = 0;
		pos = &mypos;
	}

	if (flags & ROFFNUM_WHITE)
		while (isspace((unsigned char)v[*pos]))
			(*pos)++;

	if ( ! roff_evalpar(r, ln, v, pos, res, flags))
		return 0;

	while (1) {
		if (flags & ROFFNUM_WHITE)
			while (isspace((unsigned char)v[*pos]))
				(*pos)++;

		if ( ! roff_getop(v, pos, &operator))
			break;

		if (flags & ROFFNUM_WHITE)
			while (isspace((unsigned char)v[*pos]))
				(*pos)++;

		if ( ! roff_evalpar(r, ln, v, pos, &operand2, flags))
			return 0;

		if (flags & ROFFNUM_WHITE)
			while (isspace((unsigned char)v[*pos]))
				(*pos)++;

		if (NULL == res)
			continue;

		switch (operator) {
		case '+':
			*res += operand2;
			break;
		case '-':
			*res -= operand2;
			break;
		case '*':
			*res *= operand2;
			break;
		case '/':
			if (operand2 == 0) {
				mandoc_msg(MANDOCERR_DIVZERO,
					ln, *pos, "%s", v);
				*res = 0;
				break;
			}
			*res /= operand2;
			break;
		case '%':
			if (operand2 == 0) {
				mandoc_msg(MANDOCERR_DIVZERO,
					ln, *pos, "%s", v);
				*res = 0;
				break;
			}
			*res %= operand2;
			break;
		case '<':
			*res = *res < operand2;
			break;
		case '>':
			*res = *res > operand2;
			break;
		case 'l':
			*res = *res <= operand2;
			break;
		case 'g':
			*res = *res >= operand2;
			break;
		case '=':
			*res = *res == operand2;
			break;
		case '!':
			*res = *res != operand2;
			break;
		case '&':
			*res = *res && operand2;
			break;
		case ':':
			*res = *res || operand2;
			break;
		case 'i':
			if (operand2 < *res)
				*res = operand2;
			break;
		case 'a':
			if (operand2 > *res)
				*res = operand2;
			break;
		default:
			abort();
		}
	}
	return 1;
}