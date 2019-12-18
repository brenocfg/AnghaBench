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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  fhandle_t ;

/* Variables and functions */

__attribute__((used)) static int
nfsrv_putfhname(fhandle_t *fhp, char *bufp)
{
	int i;
	uint8_t *cp;
	const uint8_t *hexdigits = "0123456789abcdef";

	cp = (uint8_t *)fhp;
	for (i = 0; i < sizeof(*fhp); i++) {
		bufp[2 * i] = hexdigits[(*cp >> 4) & 0xf];
		bufp[2 * i + 1] = hexdigits[*cp++ & 0xf];
	}
	bufp[2 * i] = '\0';
	return (2 * i);
}