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
typedef  int u_char ;
struct xlocale_collate {int /*<<< orphan*/  __collate_load_error; } ;
struct TYPE_2__ {scalar_t__* components; } ;

/* Variables and functions */
 size_t XLC_COLLATE ; 
 int /*<<< orphan*/  __collate_range_cmp (int,int) ; 
 TYPE_1__* __get_locale () ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 

__attribute__((used)) static const u_char *
__sccl(char *tab, const u_char *fmt)
{
	int c, n, v, i;
	struct xlocale_collate *table =
		(struct xlocale_collate*)__get_locale()->components[XLC_COLLATE];

	/* first `clear' the whole table */
	c = *fmt++;		/* first char hat => negated scanset */
	if (c == '^') {
		v = 1;		/* default => accept */
		c = *fmt++;	/* get new first char */
	} else
		v = 0;		/* default => reject */

	/* XXX: Will not work if sizeof(tab*) > sizeof(char) */
	(void) memset(tab, v, 256);

	if (c == 0)
		return (fmt - 1);/* format ended before closing ] */

	/*
	 * Now set the entries corresponding to the actual scanset
	 * to the opposite of the above.
	 *
	 * The first character may be ']' (or '-') without being special;
	 * the last character may be '-'.
	 */
	v = 1 - v;
	for (;;) {
		tab[c] = v;		/* take character c */
doswitch:
		n = *fmt++;		/* and examine the next */
		switch (n) {

		case 0:			/* format ended too soon */
			return (fmt - 1);

		case '-':
			/*
			 * A scanset of the form
			 *	[01+-]
			 * is defined as `the digit 0, the digit 1,
			 * the character +, the character -', but
			 * the effect of a scanset such as
			 *	[a-zA-Z0-9]
			 * is implementation defined.  The V7 Unix
			 * scanf treats `a-z' as `the letters a through
			 * z', but treats `a-a' as `the letter a, the
			 * character -, and the letter a'.
			 *
			 * For compatibility, the `-' is not considered
			 * to define a range if the character following
			 * it is either a close bracket (required by ANSI)
			 * or is not numerically greater than the character
			 * we just stored in the table (c).
			 */
			n = *fmt;
			if (n == ']'
			    || (table->__collate_load_error ? n < c :
				__collate_range_cmp(n, c) < 0
			       )
			   ) {
				c = '-';
				break;	/* resume the for(;;) */
			}
			fmt++;
			/* fill in the range */
			if (table->__collate_load_error) {
				do {
					tab[++c] = v;
				} while (c < n);
			} else {
				for (i = 0; i < 256; i ++)
					if (__collate_range_cmp(c, i) <= 0 &&
					    __collate_range_cmp(i, n) <= 0
					   )
						tab[i] = v;
			}
#if 1	/* XXX another disgusting compatibility hack */
			c = n;
			/*
			 * Alas, the V7 Unix scanf also treats formats
			 * such as [a-c-e] as `the letters a through e'.
			 * This too is permitted by the standard....
			 */
			goto doswitch;
#else
			c = *fmt++;
			if (c == 0)
				return (fmt - 1);
			if (c == ']')
				return (fmt);
#endif
			break;

		case ']':		/* end of scanset */
			return (fmt);

		default:		/* just another character */
			c = n;
			break;
		}
	}
	/* NOTREACHED */
}