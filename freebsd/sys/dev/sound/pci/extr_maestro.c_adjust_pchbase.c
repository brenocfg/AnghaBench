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
struct agg_chinfo {scalar_t__ phys; size_t base; } ;
typedef  size_t bus_addr_t ;

/* Variables and functions */
 int AGG_MAXPLAYCH ; 
 int BASE_SHIFT ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,size_t,...) ; 

__attribute__((used)) static void
adjust_pchbase(struct agg_chinfo *chans, u_int n, u_int size)
{
	struct agg_chinfo *pchs[AGG_MAXPLAYCH];
	u_int i, j, k;
	bus_addr_t base;

	/* sort pchs by phys address */
	for (i = 0; i < n; i++) {
		for (j = 0; j < i; j++)
			if (chans[i].phys < pchs[j]->phys) {
				for (k = i; k > j; k--)
					pchs[k] = pchs[k - 1];
				break;
			}
		pchs[j] = chans + i;
	}

	/* use new base register if next buffer can not be addressed
	   via current base. */
#define BASE_SHIFT (WPWA_WTBAR_SHIFT(2) + 2 + 1)
	base = pchs[0]->base;
	for (k = 1, i = 1; i < n; i++) {
		if (pchs[i]->phys + size - base >= 1 << BASE_SHIFT)
			/* not addressable: assign new base */
			base = (pchs[i]->base -= k++ << BASE_SHIFT);
		else
			pchs[i]->base = base;
	}
#undef BASE_SHIFT

	if (bootverbose) {
		printf("Total of %d bases are assigned.\n", k);
		for (i = 0; i < n; i++) {
			printf("ch.%d: phys 0x%llx, wpwa 0x%llx\n",
			       i, (long long)chans[i].phys,
			       (long long)(chans[i].phys -
					   chans[i].base) >> 1);
		}
	}
}