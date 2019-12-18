#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
struct TYPE_2__ {int /*<<< orphan*/  assid; } ;

/* Variables and functions */
 TYPE_1__* assoc_cache ; 
 scalar_t__ ntpq_dogetassoc () ; 
 int numassoc ; 

int  ntpq_read_associations ( u_short resultbuf[], int max_entries )
{
    int i = 0;

    if (ntpq_dogetassoc()) {       
        
        if(numassoc < max_entries)
          max_entries = numassoc;

        for (i=0;i<max_entries;i++)
            resultbuf[i] = assoc_cache[i].assid;

        return numassoc;
    }

    return 0;
}