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
typedef  int u_int16_t ;
struct TYPE_9__ {char* page; } ;
struct TYPE_8__ {int BSIZE; } ;
typedef  TYPE_1__ HTAB ;
typedef  TYPE_2__ BUFHEAD ;

/* Variables and functions */
 int PARTIAL_KEY ; 
 TYPE_2__* __get_buf (TYPE_1__*,int,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_collisions ; 
 scalar_t__ memcmp (char*,char*,int) ; 

int
__find_bigpair(HTAB *hashp, BUFHEAD *bufp, int ndx, char *key, int size)
{
	u_int16_t *bp;
	char *p;
	int ksize;
	u_int16_t bytes;
	char *kkey;

	bp = (u_int16_t *)bufp->page;
	p = bufp->page;
	ksize = size;
	kkey = key;

	for (bytes = hashp->BSIZE - bp[ndx];
	    bytes <= size && bp[ndx + 1] == PARTIAL_KEY;
	    bytes = hashp->BSIZE - bp[ndx]) {
		if (memcmp(p + bp[ndx], kkey, bytes))
			return (-2);
		kkey += bytes;
		ksize -= bytes;
		bufp = __get_buf(hashp, bp[ndx + 2], bufp, 0);
		if (!bufp)
			return (-3);
		p = bufp->page;
		bp = (u_int16_t *)p;
		ndx = 1;
	}

	if (bytes != ksize || memcmp(p + bp[ndx], kkey, bytes)) {
#ifdef HASH_STATISTICS
		++hash_collisions;
#endif
		return (-2);
	} else
		return (ndx);
}