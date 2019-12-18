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
struct TYPE_3__ {scalar_t__ value; int serial; } ;

/* Variables and functions */
 TYPE_1__** file ; 
 int* len ; 
 int pref ; 
 TYPE_1__** sfile ; 
 int* slen ; 
 int suff ; 

__attribute__((used)) static void
prune(void)
{
	int i, j;

	for (pref = 0; pref < len[0] && pref < len[1] &&
	    file[0][pref + 1].value == file[1][pref + 1].value;
	    pref++)
		;
	for (suff = 0; suff < len[0] - pref && suff < len[1] - pref &&
	    file[0][len[0] - suff].value == file[1][len[1] - suff].value;
	    suff++)
		;
	for (j = 0; j < 2; j++) {
		sfile[j] = file[j] + pref;
		slen[j] = len[j] - pref - suff;
		for (i = 0; i <= slen[j]; i++)
			sfile[j][i].serial = i;
	}
}