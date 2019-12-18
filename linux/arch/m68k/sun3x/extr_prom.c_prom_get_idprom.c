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
 scalar_t__ SUN3X_IDPROM ; 

unsigned char
prom_get_idprom(char *idbuf, int num_bytes)
{
        int i;

	/* make a copy of the idprom structure */
	for (i = 0; i < num_bytes; i++)
		idbuf[i] = ((char *)SUN3X_IDPROM)[i];

        return idbuf[0];
}