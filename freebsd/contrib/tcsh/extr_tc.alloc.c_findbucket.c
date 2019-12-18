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
union overhead {union overhead* ov_next; } ;

/* Variables and functions */
 size_t NBUCKETS ; 
 union overhead** nextf ; 

__attribute__((used)) static int
findbucket(union overhead *freep, int srchlen)
{
    union overhead *p;
    size_t i;
    int j;

    for (i = 0; i < NBUCKETS; i++) {
	j = 0;
	for (p = nextf[i]; p && j != srchlen; p = p->ov_next) {
	    if (p == freep)
		return (i);
	    j++;
	}
    }
    return (-1);
}