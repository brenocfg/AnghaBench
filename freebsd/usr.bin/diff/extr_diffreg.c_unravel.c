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
struct cand {scalar_t__ y; int pred; int x; } ;

/* Variables and functions */
 int* J ; 
 struct cand* clist ; 
 int* len ; 
 int pref ; 
 int suff ; 

__attribute__((used)) static void
unravel(int p)
{
	struct cand *q;
	int i;

	for (i = 0; i <= len[0]; i++)
		J[i] = i <= pref ? i :
		    i > len[0] - suff ? i + len[1] - len[0] : 0;
	for (q = clist + p; q->y != 0; q = clist + q->pred)
		J[q->x + pref] = q->y + pref;
}