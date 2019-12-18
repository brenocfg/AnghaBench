#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* buf; } ;
typedef  TYPE_1__ CStr ;

/* Variables and functions */
 int KillPos ; 
 TYPE_1__* KillRing ; 
 int KillRingLen ; 
 int KillRingMax ; 
 int YankPos ; 
 TYPE_1__* xcalloc (int,int) ; 
 int /*<<< orphan*/  xfree (TYPE_1__*) ; 

void
SetKillRing(int max)
{
    CStr *new;
    int count, i, j;

    if (max < 1)
	max = 1;		/* no ring, but always one buffer */
    if (max == KillRingMax)
	return;
    new = xcalloc(max, sizeof(CStr));
    if (KillRing != NULL) {
	if (KillRingLen != 0) {
	    if (max >= KillRingLen) {
		count = KillRingLen;
		j = KillPos;
	    } else {
		count = max;
		j = (KillPos - count + KillRingLen) % KillRingLen;
	    }
	    for (i = 0; i < KillRingLen; i++) {
		if (i < count)	/* copy latest */
		    new[i] = KillRing[j];
		else		/* free the others */
		    xfree(KillRing[j].buf);
		j = (j + 1) % KillRingLen;
	    }
	    KillRingLen = count;
	    KillPos = count % max;
	    YankPos = count - 1;
	}
	xfree(KillRing);
    }
    KillRing = new;
    KillRingMax = max;
}