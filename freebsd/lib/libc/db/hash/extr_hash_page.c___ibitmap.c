#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  scalar_t__ u_int16_t ;
struct TYPE_3__ {int BSIZE; int** mapp; scalar_t__* BITMAPS; int /*<<< orphan*/  nmaps; } ;
typedef  TYPE_1__ HTAB ;

/* Variables and functions */
 int ALL_SET ; 
 int BYTE_MASK ; 
 int INT_BYTE_SHIFT ; 
 int INT_TO_BYTE ; 
 int /*<<< orphan*/  SETBIT (int*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 

int
__ibitmap(HTAB *hashp, int pnum, int nbits, int ndx)
{
	u_int32_t *ip;
	int clearbytes, clearints;

	if ((ip = (u_int32_t *)malloc(hashp->BSIZE)) == NULL)
		return (1);
	hashp->nmaps++;
	clearints = ((nbits - 1) >> INT_BYTE_SHIFT) + 1;
	clearbytes = clearints << INT_TO_BYTE;
	(void)memset((char *)ip, 0, clearbytes);
	(void)memset(((char *)ip) + clearbytes, 0xFF,
	    hashp->BSIZE - clearbytes);
	ip[clearints - 1] = ALL_SET << (nbits & BYTE_MASK);
	SETBIT(ip, 0);
	hashp->BITMAPS[ndx] = (u_int16_t)pnum;
	hashp->mapp[ndx] = ip;
	return (0);
}