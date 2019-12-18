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
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  va_list ;
typedef  union arg {int dummy; } arg ;
typedef  int u_int ;
struct typetable {int nextarg; } ;

/* Variables and functions */
 int CHARINT ; 
 int INTMAXT ; 
 int LLONGINT ; 
 int LONGDBL ; 
 int LONGINT ; 
 int MAX_POSARG ; 
 int PTRDIFFT ; 
 int SHORTINT ; 
 int SIZET ; 
 int /*<<< orphan*/  TP_CHAR ; 
 int /*<<< orphan*/  TP_INT ; 
 int /*<<< orphan*/  TP_INTMAXT ; 
 int /*<<< orphan*/  TP_LLONG ; 
 int /*<<< orphan*/  TP_LONG ; 
 int /*<<< orphan*/  TP_PTRDIFFT ; 
 int /*<<< orphan*/  TP_SCHAR ; 
 int /*<<< orphan*/  TP_SHORT ; 
 int /*<<< orphan*/  TP_SSIZET ; 
 int /*<<< orphan*/  TP_VOID ; 
 int /*<<< orphan*/  TP_WCHAR ; 
 int /*<<< orphan*/  T_DOUBLE ; 
 int /*<<< orphan*/  T_INT ; 
 int /*<<< orphan*/  T_LONG_DOUBLE ; 
 int /*<<< orphan*/  T_WINT ; 
 int addsarg (struct typetable*,int) ; 
 int addtype (struct typetable*,int /*<<< orphan*/ ) ; 
 int adduarg (struct typetable*,int) ; 
 int addwaster (struct typetable*,char**) ; 
 int /*<<< orphan*/  build_arg_table (struct typetable*,int /*<<< orphan*/ ,union arg**) ; 
 int /*<<< orphan*/  freetypes (struct typetable*) ; 
 int /*<<< orphan*/  inittypes (struct typetable*) ; 
 int /*<<< orphan*/  is_digit (char) ; 
 int /*<<< orphan*/  to_digit (char) ; 

int
__find_warguments (const wchar_t *fmt0, va_list ap, union arg **argtable)
{
	wchar_t *fmt;		/* format string */
	wchar_t ch;		/* character from fmt */
	u_int n;		/* handy integer (short term usage) */
	int error;
	int flags;		/* flags as above */
	struct typetable types;	/* table of types */

	fmt = (wchar_t *)fmt0;
	inittypes(&types);
	error = 0;

	/*
	 * Scan the format for conversions (`%' character).
	 */
	for (;;) {
		while ((ch = *fmt) != '\0' && ch != '%')
			fmt++;
		if (ch == '\0')
			goto done;
		fmt++;		/* skip over '%' */

		flags = 0;

rflag:		ch = *fmt++;
reswitch:	switch (ch) {
		case ' ':
		case '#':
			goto rflag;
		case '*':
			if ((error = addwaster(&types, &fmt)))
				goto error;
			goto rflag;
		case '-':
		case '+':
		case '\'':
			goto rflag;
		case '.':
			if ((ch = *fmt++) == '*') {
				if ((error = addwaster(&types, &fmt)))
					goto error;
				goto rflag;
			}
			while (is_digit(ch)) {
				ch = *fmt++;
			}
			goto reswitch;
		case '0':
			goto rflag;
		case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			n = 0;
			do {
				n = 10 * n + to_digit(ch);
				/* Detect overflow */
				if (n > MAX_POSARG) {
					error = -1;
					goto error;
				}
				ch = *fmt++;
			} while (is_digit(ch));
			if (ch == '$') {
				types.nextarg = n;
				goto rflag;
			}
			goto reswitch;
#ifndef NO_FLOATING_POINT
		case 'L':
			flags |= LONGDBL;
			goto rflag;
#endif
		case 'h':
			if (flags & SHORTINT) {
				flags &= ~SHORTINT;
				flags |= CHARINT;
			} else
				flags |= SHORTINT;
			goto rflag;
		case 'j':
			flags |= INTMAXT;
			goto rflag;
		case 'l':
			if (flags & LONGINT) {
				flags &= ~LONGINT;
				flags |= LLONGINT;
			} else
				flags |= LONGINT;
			goto rflag;
		case 'q':
			flags |= LLONGINT;	/* not necessarily */
			goto rflag;
		case 't':
			flags |= PTRDIFFT;
			goto rflag;
		case 'z':
			flags |= SIZET;
			goto rflag;
		case 'C':
			flags |= LONGINT;
			/*FALLTHROUGH*/
		case 'c':
			error = addtype(&types,
					(flags & LONGINT) ? T_WINT : T_INT);
			if (error)
				goto error;
			break;
		case 'D':
			flags |= LONGINT;
			/*FALLTHROUGH*/
		case 'd':
		case 'i':
			if ((error = addsarg(&types, flags)))
				goto error;
			break;
#ifndef NO_FLOATING_POINT
		case 'a':
		case 'A':
		case 'e':
		case 'E':
		case 'f':
		case 'g':
		case 'G':
			error = addtype(&types,
			    (flags & LONGDBL) ? T_LONG_DOUBLE : T_DOUBLE);
			if (error)
				goto error;
			break;
#endif /* !NO_FLOATING_POINT */
		case 'n':
			if (flags & INTMAXT)
				error = addtype(&types, TP_INTMAXT);
			else if (flags & PTRDIFFT)
				error = addtype(&types, TP_PTRDIFFT);
			else if (flags & SIZET)
				error = addtype(&types, TP_SSIZET);
			else if (flags & LLONGINT)
				error = addtype(&types, TP_LLONG);
			else if (flags & LONGINT)
				error = addtype(&types, TP_LONG);
			else if (flags & SHORTINT)
				error = addtype(&types, TP_SHORT);
			else if (flags & CHARINT)
				error = addtype(&types, TP_SCHAR);
			else
				error = addtype(&types, TP_INT);
			if (error)
				goto error;
			continue;	/* no output */
		case 'O':
			flags |= LONGINT;
			/*FALLTHROUGH*/
		case 'o':
			if ((error = adduarg(&types, flags)))
				goto error;
			break;
		case 'p':
			if ((error = addtype(&types, TP_VOID)))
				goto error;
			break;
		case 'S':
			flags |= LONGINT;
			/*FALLTHROUGH*/
		case 's':
			error = addtype(&types,
			    (flags & LONGINT) ? TP_WCHAR : TP_CHAR);
			if (error)
				goto error;
			break;
		case 'U':
			flags |= LONGINT;
			/*FALLTHROUGH*/
		case 'u':
		case 'X':
		case 'x':
			if ((error = adduarg(&types, flags)))
				goto error;
			break;
		default:	/* "%?" prints ?, unless ? is NUL */
			if (ch == '\0')
				goto done;
			break;
		}
	}
done:
	build_arg_table(&types, ap, argtable);
error:
	freetypes(&types);
	return (error || *argtable == NULL);
}