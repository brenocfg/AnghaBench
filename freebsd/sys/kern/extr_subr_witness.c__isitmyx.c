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
struct witness {int w_index; char* w_name; } ;

/* Variables and functions */
 unsigned char WITNESS_ATOD (unsigned char) ; 
 unsigned char WITNESS_DTOA (unsigned char) ; 
 int /*<<< orphan*/  WITNESS_INDEX_ASSERT (int) ; 
 unsigned char WITNESS_RELATED_MASK ; 
 int /*<<< orphan*/  kdb_backtrace () ; 
 int /*<<< orphan*/  mtx_owned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  w_mtx ; 
 unsigned char** w_rmatrix ; 
 int witness_watch ; 

__attribute__((used)) static int
_isitmyx(struct witness *w1, struct witness *w2, int rmask, const char *fname)
{
	unsigned char r1, r2;
	int i1, i2;

	i1 = w1->w_index;
	i2 = w2->w_index;
	WITNESS_INDEX_ASSERT(i1);
	WITNESS_INDEX_ASSERT(i2);
	r1 = w_rmatrix[i1][i2] & WITNESS_RELATED_MASK;
	r2 = w_rmatrix[i2][i1] & WITNESS_RELATED_MASK;

	/* The flags on one better be the inverse of the flags on the other */
	if (!((WITNESS_ATOD(r1) == r2 && WITNESS_DTOA(r2) == r1) ||
	    (WITNESS_DTOA(r1) == r2 && WITNESS_ATOD(r2) == r1))) {
		/* Don't squawk if we're potentially racing with an update. */
		if (!mtx_owned(&w_mtx))
			return (0);
		printf("%s: rmatrix mismatch between %s (index %d) and %s "
		    "(index %d): w_rmatrix[%d][%d] == %hhx but "
		    "w_rmatrix[%d][%d] == %hhx\n",
		    fname, w1->w_name, i1, w2->w_name, i2, i1, i2, r1,
		    i2, i1, r2);
		kdb_backtrace();
		printf("Witness disabled.\n");
		witness_watch = -1;
	}
	return (r1 & rmask);
}