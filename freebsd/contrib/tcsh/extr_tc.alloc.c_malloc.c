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
union overhead {int ov_index; void* ov_rmagic; scalar_t__ ov_size; int /*<<< orphan*/  ov_magic; union overhead* ov_next; } ;
typedef  int /*<<< orphan*/  memalign_t ;
typedef  scalar_t__ caddr_t ;
typedef  scalar_t__ U_short ;
typedef  void* U_int ;

/* Variables and functions */
 int /*<<< orphan*/  CGETS (int,int,char*) ; 
 int /*<<< orphan*/  MAGIC ; 
 size_t MEMALIGN (int) ; 
 void* RMAGIC ; 
 size_t RSLOP ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  child ; 
 int /*<<< orphan*/  morecore (int) ; 
 union overhead** nextf ; 
 int /*<<< orphan*/ * nmalloc ; 
 int /*<<< orphan*/  out_of_memory () ; 
 int /*<<< orphan*/  showall (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprintf (int /*<<< orphan*/ ,size_t) ; 

memalign_t
malloc(size_t nbytes)
{
#ifndef lint
    union overhead *p;
    int bucket = 0;
    unsigned shiftr;

    /*
     * Convert amount of memory requested into closest block size stored in
     * hash buckets which satisfies request.  Account for space used per block
     * for accounting.
     */
#ifdef SUNOS4
    /*
     * SunOS localtime() overwrites the 9th byte on an 8 byte malloc()....
     * so we get one more...
     * From Michael Schroeder: This is not true. It depends on the 
     * timezone string. In Europe it can overwrite the 13th byte on a
     * 12 byte malloc.
     * So we punt and we always allocate an extra byte.
     */
    nbytes++;
#endif

    nbytes = MEMALIGN(MEMALIGN(sizeof(union overhead)) + nbytes + RSLOP);
    shiftr = (nbytes - 1) >> 2;

    /* apart from this loop, this is O(1) */
    while ((shiftr >>= 1) != 0)
	bucket++;
    /*
     * If nothing in hash bucket right now, request more memory from the
     * system.
     */
    if (nextf[bucket] == NULL)
	morecore(bucket);
    if ((p = nextf[bucket]) == NULL) {
	child++;
#ifndef DEBUG
	out_of_memory();
#else
	showall(NULL, NULL);
	xprintf(CGETS(19, 1, "nbytes=%zu: Out of memory\n"), nbytes);
	abort();
#endif
	/* fool lint */
	return ((memalign_t) 0);
    }
    /* remove from linked list */
    nextf[bucket] = nextf[bucket]->ov_next;
    p->ov_magic = MAGIC;
    p->ov_index = bucket;
    nmalloc[bucket]++;
#ifdef RCHECK
    /*
     * Record allocated size of block and bound space with magic numbers.
     */
    p->ov_size = (p->ov_index <= 13) ? (U_short)nbytes - 1 : 0;
    p->ov_rmagic = RMAGIC;
    *((U_int *) (((caddr_t) p) + nbytes - RSLOP)) = RMAGIC;
#endif
    return ((memalign_t) (((caddr_t) p) + MEMALIGN(sizeof(union overhead))));
#else
    if (nbytes)
	return ((memalign_t) 0);
    else
	return ((memalign_t) 0);
#endif /* !lint */
}