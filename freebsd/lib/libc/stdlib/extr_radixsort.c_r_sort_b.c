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
typedef  int u_int ;
typedef  size_t u_char ;
typedef  int /*<<< orphan*/  stack ;

/* Variables and functions */
 int SIZE ; 
 int THRESHOLD ; 
 int /*<<< orphan*/  empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pop (size_t const**,int,int) ; 
 int /*<<< orphan*/  push (size_t const**,int,int) ; 
 int /*<<< orphan*/  simplesort (size_t const**,int,int,size_t const*,int) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
r_sort_b(const u_char **a, const u_char **ta, int n, int i, const u_char *tr,
    u_int endch)
{
	static int count[256], nc, bmin;
	int c;
	const u_char **ak, **ai;
	stack s[512], *sp, *sp0, *sp1, temp;
	const u_char **top[256];
	int *cp, bigc;

	sp = s;
	push(a, n, i);
	while (!empty(s)) {
		pop(a, n, i);
		if (n < THRESHOLD) {
			simplesort(a, n, i, tr, endch);
			continue;
		}

		if (nc == 0) {
			bmin = 255;
			for (ak = a + n; --ak >= a;) {
				c = tr[(*ak)[i]];
				if (++count[c] == 1 && c != endch) {
					if (c < bmin)
						bmin = c;
					nc++;
				}
			}
			if (sp + nc > s + SIZE) {
				r_sort_b(a, ta, n, i, tr, endch);
				continue;
			}
		}

		sp0 = sp1 = sp;
		bigc = 2;
		if (endch == 0) {
			top[0] = ak = a + count[0];
			count[0] = 0;
		} else {
			ak = a;
			top[255] = a + n;
			count[255] = 0;
		}
		for (cp = count + bmin; nc > 0; cp++) {
			while (*cp == 0)
				cp++;
			if ((c = *cp) > 1) {
				if (c > bigc) {
					bigc = c;
					sp1 = sp;
				}
				push(ak, c, i+1);
			}
			top[cp-count] = ak += c;
			*cp = 0;			/* Reset count[]. */
			nc--;
		}
		swap(*sp0, *sp1, temp);

		for (ak = ta + n, ai = a+n; ak > ta;)	/* Copy to temp. */
			*--ak = *--ai;
		for (ak = ta+n; --ak >= ta;)		/* Deal to piles. */
			*--top[tr[(*ak)[i]]] = *ak;
	}
}