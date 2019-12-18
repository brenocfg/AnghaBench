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

/* Variables and functions */
 int istrsenvisx (char**,int /*<<< orphan*/ *,char*,int,int,char const*,int /*<<< orphan*/ *) ; 

char *
svis(char *mbdst, int c, int flags, int nextc, const char *mbextra)
{
	char cc[2];
	int ret;

	cc[0] = c;
	cc[1] = nextc;

	ret = istrsenvisx(&mbdst, NULL, cc, 1, flags, mbextra, NULL);
	if (ret < 0)
		return NULL;
	return mbdst + ret;
}