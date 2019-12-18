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
typedef  int quad_t ;

/* Variables and functions */
 char** SPBuf ; 
 size_t SPIndex ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static char * 
sperc2(int ttl, int misses)
{
	char *p = SPBuf[SPIndex];

	if (ttl) {
		sprintf(p, "%3d%%",
		    (int)(char)((quad_t)(ttl - misses) * 100 / ttl));
	} else {
		sprintf(p, "   -");
	}
	SPIndex = (SPIndex + 1) & 63;
	return(p);
}