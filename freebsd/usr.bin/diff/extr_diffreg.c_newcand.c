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
struct cand {int x; int y; int pred; } ;

/* Variables and functions */
 int clen ; 
 struct cand* clist ; 
 int clistlen ; 
 struct cand* xreallocarray (struct cand*,int,int) ; 

__attribute__((used)) static int
newcand(int x, int y, int pred)
{
	struct cand *q;

	if (clen == clistlen) {
		clistlen = clistlen * 11 / 10;
		clist = xreallocarray(clist, clistlen, sizeof(*clist));
	}
	q = clist + clen;
	q->x = x;
	q->y = y;
	q->pred = pred;
	return (clen++);
}