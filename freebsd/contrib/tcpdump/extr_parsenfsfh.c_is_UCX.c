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
typedef  int u_int ;

/* Variables and functions */
 scalar_t__ ND_ISPRINT (unsigned char const) ; 

__attribute__((used)) static int
is_UCX(const unsigned char *fhp, u_int len)
{
	register u_int i;
	int seen_null = 0;

	/*
	 * Require at least 28 bytes of file handle; it's variable-length
	 * in NFSv3.  "len" is in units of 32-bit words, not bytes.
	 */
	if (len < 28/4)
		return(0);

	for (i = 1; i < 14; i++) {
	    if (ND_ISPRINT(fhp[i])) {
		if (seen_null)
		   return(0);
		else
		   continue;
	    }
	    else if (fhp[i] == 0) {
		seen_null = 1;
		continue;
	    }
	    else
		return(0);
	}

	return(1);
}