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
typedef  int /*<<< orphan*/  u_int8_t ;

/* Variables and functions */
 int EAI_MEMORY ; 
 int snprintf (char*,size_t,char*,char*,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int
hexname(const u_int8_t *cp, size_t len, char *host, size_t hostlen)
{
	int i, n;
	char *outp = host;

	*outp = '\0';
	for (i = 0; i < len; i++) {
		n = snprintf(outp, hostlen, "%s%02x",
		    i ? ":" : "", cp[i]);
		if (n < 0 || n >= hostlen) {
			*host = '\0';
			return EAI_MEMORY;
		}
		outp += n;
		hostlen -= n;
	}
	return 0;
}