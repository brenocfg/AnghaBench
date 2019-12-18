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
typedef  size_t const* stack ;

/* Variables and functions */
 int SIZE ; 
 int THRESHOLD ; 
 int /*<<< orphan*/  empty (size_t const**) ; 
 int /*<<< orphan*/  pop (size_t const**,int,int) ; 
 int /*<<< orphan*/  push (size_t const**,int,int) ; 
 int /*<<< orphan*/  simplesort (size_t const**,int,int,size_t const*,int) ; 
 int /*<<< orphan*/  swap (size_t const*,size_t const*,size_t const*) ; 

__attribute__((used)) static void
r_sort_a(const u_char **a, int n, int i, const u_char *tr, u_int endch)
{
	static int count[256], nc, bmin;
	int c;
	const u_char **ak, *r;
	stack s[SIZE], *sp, *sp0, *sp1, temp;
	int *cp, bigc;
	const u_char **an, *t, **aj, **top[256];

	/* Set up stack. */
	sp = s;
	push(a, n, i);
	while (!empty(s)) {
		pop(a, n, i);
		if (n < THRESHOLD) {
			simplesort(a, n, i, tr, endch);
			continue;
		}
		an = a + n;

		/* Make character histogram. */
		if (nc == 0) {
			bmin = 255;	/* First occupied bin, excluding eos. */
			for (ak = a; ak < an;) {
				c = tr[(*ak++)[i]];
				if (++count[c] == 1 && c != endch) {
					if (c < bmin)
						bmin = c;
					nc++;
				}
			}
			if (sp + nc > s + SIZE) {	/* Get more stack. */
				r_sort_a(a, n, i, tr, endch);
				continue;
			}
		}

		/*
		 * Special case: if all strings have the same
		 * character at position i, move on to the next
		 * character.
		 */
		if (nc == 1 && count[bmin] == n) {
			push(a, n, i+1);
			nc = count[bmin] = 0;
			continue;
		}

		/*
		 * Set top[]; push incompletely sorted bins onto stack.
		 * top[] = pointers to last out-of-place element in bins.
		 * count[] = counts of elements in bins.
		 * Before permuting: top[c-1] + count[c] = top[c];
		 * during deal: top[c] counts down to top[c-1].
		 */
		sp0 = sp1 = sp;		/* Stack position of biggest bin. */
		bigc = 2;		/* Size of biggest bin. */
		if (endch == 0)		/* Special case: set top[eos]. */
			top[0] = ak = a + count[0];
		else {
			ak = a;
			top[255] = an;
		}
		for (cp = count + bmin; nc > 0; cp++) {
			while (*cp == 0)	/* Find next non-empty pile. */
				cp++;
			if (*cp > 1) {
				if (*cp > bigc) {
					bigc = *cp;
					sp1 = sp;
				}
				push(ak, *cp, i+1);
			}
			top[cp-count] = ak += *cp;
			nc--;
		}
		swap(*sp0, *sp1, temp);	/* Play it safe -- biggest bin last. */

		/*
		 * Permute misplacements home.  Already home: everything
		 * before aj, and in bin[c], items from top[c] on.
		 * Inner loop:
		 *	r = next element to put in place;
		 *	ak = top[r[i]] = location to put the next element.
		 *	aj = bottom of 1st disordered bin.
		 * Outer loop:
		 *	Once the 1st disordered bin is done, ie. aj >= ak,
		 *	aj<-aj + count[c] connects the bins in a linked list;
		 *	reset count[c].
		 */
		for (aj = a; aj < an;  *aj = r, aj += count[c], count[c] = 0)
			for (r = *aj;  aj < (ak = --top[c = tr[r[i]]]);)
				swap(*ak, r, t);
	}
}