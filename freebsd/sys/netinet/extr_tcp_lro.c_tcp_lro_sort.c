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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct lro_mbuf_sort {int seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int tcp_lro_msb_64 (int) ; 

__attribute__((used)) static void
tcp_lro_sort(struct lro_mbuf_sort *parray, uint32_t size)
{
	struct lro_mbuf_sort temp;
	uint64_t ones;
	uint64_t zeros;
	uint32_t x;
	uint32_t y;

repeat:
	/* for small arrays insertion sort is faster */
	if (size <= 12) {
		for (x = 1; x < size; x++) {
			temp = parray[x];
			for (y = x; y > 0 && temp.seq < parray[y - 1].seq; y--)
				parray[y] = parray[y - 1];
			parray[y] = temp;
		}
		return;
	}

	/* compute sequence bits which are constant */
	ones = 0;
	zeros = 0;
	for (x = 0; x != size; x++) {
		ones |= parray[x].seq;
		zeros |= ~parray[x].seq;
	}

	/* compute bits which are not constant into "ones" */
	ones &= zeros;
	if (ones == 0)
		return;

	/* pick the most significant bit which is not constant */
	ones = tcp_lro_msb_64(ones);

	/*
	 * Move entries having cleared sequence bits to the beginning
	 * of the array:
	 */
	for (x = y = 0; y != size; y++) {
		/* skip set bits */
		if (parray[y].seq & ones)
			continue;
		/* swap entries */
		temp = parray[x];
		parray[x] = parray[y];
		parray[y] = temp;
		x++;
	}

	KASSERT(x != 0 && x != size, ("Memory is corrupted\n"));

	/* sort zeros */
	tcp_lro_sort(parray, x);

	/* sort ones */
	parray += x;
	size -= x;
	goto repeat;
}