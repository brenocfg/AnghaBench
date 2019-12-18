#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int u_int16_t ;
struct TYPE_9__ {int addr; } ;
struct TYPE_8__ {int* SPARES; int LAST_FREED; int BSHIFT; int BSIZE; int /*<<< orphan*/ ** mapp; } ;
typedef  TYPE_1__ HTAB ;
typedef  TYPE_2__ BUFHEAD ;

/* Variables and functions */
 int BYTE_SHIFT ; 
 int /*<<< orphan*/  CLRBIT (int /*<<< orphan*/ *,int) ; 
 int SPLITMASK ; 
 int SPLITSHIFT ; 
 int /*<<< orphan*/  __reclaim_buf (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fetch_bitmap (TYPE_1__*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  stderr ; 

void
__free_ovflpage(HTAB *hashp, BUFHEAD *obufp)
{
	u_int16_t addr;
	u_int32_t *freep;
	int bit_address, free_page, free_bit;
	u_int16_t ndx;

	addr = obufp->addr;
#ifdef DEBUG1
	(void)fprintf(stderr, "Freeing %d\n", addr);
#endif
	ndx = (((u_int16_t)addr) >> SPLITSHIFT);
	bit_address =
	    (ndx ? hashp->SPARES[ndx - 1] : 0) + (addr & SPLITMASK) - 1;
	 if (bit_address < hashp->LAST_FREED)
		hashp->LAST_FREED = bit_address;
	free_page = (bit_address >> (hashp->BSHIFT + BYTE_SHIFT));
	free_bit = bit_address & ((hashp->BSIZE << BYTE_SHIFT) - 1);

	if (!(freep = hashp->mapp[free_page]))
		freep = fetch_bitmap(hashp, free_page);
#ifdef DEBUG
	/*
	 * This had better never happen.  It means we tried to read a bitmap
	 * that has already had overflow pages allocated off it, and we
	 * failed to read it from the file.
	 */
	if (!freep)
		assert(0);
#endif
	CLRBIT(freep, free_bit);
#ifdef DEBUG2
	(void)fprintf(stderr, "FREE_OVFLPAGE: ADDR: %d BIT: %d PAGE %d\n",
	    obufp->addr, free_bit, free_page);
#endif
	__reclaim_buf(hashp, obufp);
}