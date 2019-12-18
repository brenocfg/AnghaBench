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
typedef  size_t u_int ;
typedef  size_t u_char ;

/* Variables and functions */
 int /*<<< orphan*/  swap (size_t const*,size_t const*,size_t const*) ; 

__attribute__((used)) static inline void
simplesort(const u_char **a, int n, int b, const u_char *tr, u_int endch)
{
	u_char ch;
	const u_char  **ak, **ai, *s, *t;

	for (ak = a+1; --n >= 1; ak++)
		for (ai = ak; ai > a; ai--) {
			for (s = ai[0] + b, t = ai[-1] + b;
			    (ch = tr[*s]) != endch; s++, t++)
				if (ch != tr[*t])
					break;
			if (ch >= tr[*t])
				break;
			swap(ai[0], ai[-1], s);
		}
}