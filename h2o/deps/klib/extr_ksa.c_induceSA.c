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
typedef  size_t saint_t ;

/* Variables and functions */
 size_t chr (size_t) ; 
 int /*<<< orphan*/  getBuckets (size_t*,size_t*,size_t,int) ; 
 int /*<<< orphan*/  getCounts (unsigned char const*,size_t*,size_t,size_t,size_t) ; 

__attribute__((used)) static void induceSA(const unsigned char *T, saint_t *SA, saint_t *C, saint_t *B, saint_t n, saint_t k, saint_t cs)
{
	saint_t *b, i, j;
	saint_t  c0, c1;
	/* left-to-right induced sort (for L-type) */
	if (C == B) getCounts(T, C, n, k, cs);
	getBuckets(C, B, k, 0);	/* find starts of buckets */
	for (i = 0, b = 0, c1 = -1; i < n; ++i) {
		j = SA[i], SA[i] = ~j;
		if (0 < j) { /* >0 if j-1 is L-type; <0 if S-type; ==0 undefined */
			--j;
			if ((c0 = chr(j)) != c1) {
				B[c1 > 0? c1 : 0] = b - SA;
				c1 = c0;
				b = SA + B[c1 > 0? c1 : 0];
			}
			*b++ = (0 < j && chr(j - 1) < c1) ? ~j : j;
		}
	}
	/* right-to-left induced sort (for S-type) */
	if (C == B) getCounts(T, C, n, k, cs);
	getBuckets(C, B, k, 1);	/* find ends of buckets */
	for (i = n - 1, b = 0, c1 = -1; 0 <= i; --i) {
		if (0 < (j = SA[i])) { /* the prefix is S-type */
			--j;
			if ((c0 = chr(j)) != c1) {
				B[c1 > 0? c1 : 0] = b - SA;
				c1 = c0;
				b = SA + B[c1 > 0? c1 : 0];
			}
			if (c0 > 0) *--b = (j == 0 || chr(j - 1) > c1) ? ~j : j;
		} else SA[i] = ~j; /* if L-type, change the sign */
	}
}