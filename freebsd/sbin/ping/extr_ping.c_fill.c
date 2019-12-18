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
typedef  size_t u_int ;

/* Variables and functions */
 int /*<<< orphan*/  EX_USAGE ; 
 int F_QUIET ; 
 size_t TIMEVAL_LEN ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  isxdigit (char) ; 
 size_t maxpayload ; 
 int options ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 size_t sscanf (char*,char*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*) ; 

__attribute__((used)) static void
fill(char *bp, char *patp)
{
	char *cp;
	int pat[16];
	u_int ii, jj, kk;

	for (cp = patp; *cp; cp++) {
		if (!isxdigit(*cp))
			errx(EX_USAGE,
			    "patterns must be specified as hex digits");

	}
	ii = sscanf(patp,
	    "%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x",
	    &pat[0], &pat[1], &pat[2], &pat[3], &pat[4], &pat[5], &pat[6],
	    &pat[7], &pat[8], &pat[9], &pat[10], &pat[11], &pat[12],
	    &pat[13], &pat[14], &pat[15]);

	if (ii > 0)
		for (kk = 0; kk <= maxpayload - (TIMEVAL_LEN + ii); kk += ii)
			for (jj = 0; jj < ii; ++jj)
				bp[jj + kk] = pat[jj];
	if (!(options & F_QUIET)) {
		(void)printf("PATTERN: 0x");
		for (jj = 0; jj < ii; ++jj)
			(void)printf("%02x", bp[jj] & 0xFF);
		(void)printf("\n");
	}
}