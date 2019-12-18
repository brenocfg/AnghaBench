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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  cmp_t ;

/* Variables and functions */
 scalar_t__ CMP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** EVAL (int /*<<< orphan*/ *) ; 
 int THRESHOLD ; 
 int /*<<< orphan*/  insertionsort (int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reverse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
setup(u_char *list1, u_char *list2, size_t n, size_t size, cmp_t cmp)
{
	int i, length, size2, tmp, sense;
	u_char *f1, *f2, *s, *l2, *last, *p2;

	size2 = size*2;
	if (n <= 5) {
		insertionsort(list1, n, size, cmp);
		*EVAL(list2) = (u_char*) list2 + n*size;
		return;
	}
	/*
	 * Avoid running pointers out of bounds; limit n to evens
	 * for simplicity.
	 */
	i = 4 + (n & 1);
	insertionsort(list1 + (n - i) * size, i, size, cmp);
	last = list1 + size * (n - i);
	*EVAL(list2 + (last - list1)) = list2 + n * size;

#ifdef NATURAL
	p2 = list2;
	f1 = list1;
	sense = (CMP(f1, f1 + size) > 0);
	for (; f1 < last; sense = !sense) {
		length = 2;
					/* Find pairs with same sense. */
		for (f2 = f1 + size2; f2 < last; f2 += size2) {
			if ((CMP(f2, f2+ size) > 0) != sense)
				break;
			length += 2;
		}
		if (length < THRESHOLD) {		/* Pairwise merge */
			do {
				p2 = *EVAL(p2) = f1 + size2 - list1 + list2;
				if (sense > 0)
					swap (f1, f1 + size);
			} while ((f1 += size2) < f2);
		} else {				/* Natural merge */
			l2 = f2;
			for (f2 = f1 + size2; f2 < l2; f2 += size2) {
				if ((CMP(f2-size, f2) > 0) != sense) {
					p2 = *EVAL(p2) = f2 - list1 + list2;
					if (sense > 0)
						reverse(f1, f2-size);
					f1 = f2;
				}
			}
			if (sense > 0)
				reverse (f1, f2-size);
			f1 = f2;
			if (f2 < last || CMP(f2 - size, f2) > 0)
				p2 = *EVAL(p2) = f2 - list1 + list2;
			else
				p2 = *EVAL(p2) = list2 + n*size;
		}
	}
#else		/* pairwise merge only. */
	for (f1 = list1, p2 = list2; f1 < last; f1 += size2) {
		p2 = *EVAL(p2) = p2 + size2;
		if (CMP (f1, f1 + size) > 0)
			swap(f1, f1 + size);
	}
#endif /* NATURAL */
}