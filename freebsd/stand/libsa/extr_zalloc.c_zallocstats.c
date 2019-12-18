#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int mr_Bytes; struct TYPE_5__* mr_Next; } ;
struct TYPE_4__ {char* mp_End; scalar_t__ mp_Base; TYPE_2__* mp_First; scalar_t__ mp_Size; } ;
typedef  TYPE_1__ MemPool ;
typedef  TYPE_2__ MemNode ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,...) ; 

void
zallocstats(MemPool *mp)
{
	int abytes = 0;
	int hbytes = 0;
	int fcount = 0;
	MemNode *mn;

	printf("%d bytes reserved", (int)mp->mp_Size);

	mn = mp->mp_First;

	if ((void *)mn != (void *)mp->mp_Base) {
		abytes += (char *)mn - (char *)mp->mp_Base;
	}

	while (mn != NULL) {
		if ((char *)mn + mn->mr_Bytes != mp->mp_End) {
			hbytes += mn->mr_Bytes;
			++fcount;
		}
		if (mn->mr_Next != NULL) {
			abytes += (char *)mn->mr_Next -
			    ((char *)mn + mn->mr_Bytes);
		}
		mn = mn->mr_Next;
	}
	printf(" %d bytes allocated\n%d fragments (%d bytes fragmented)\n",
	    abytes, fcount, hbytes);
}