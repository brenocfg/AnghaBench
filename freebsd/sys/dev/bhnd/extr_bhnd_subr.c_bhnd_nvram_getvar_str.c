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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NVRAM_TYPE_STRING ; 
 int bhnd_nvram_getvar (int /*<<< orphan*/ ,char const*,char*,size_t*,int /*<<< orphan*/ ) ; 

int
bhnd_nvram_getvar_str(device_t dev, const char *name, char *buf, size_t len,
    size_t *rlen)
{
	size_t	larg;
	int	error;

	larg = len;
	error = bhnd_nvram_getvar(dev, name, buf, &larg,
	    BHND_NVRAM_TYPE_STRING);
	if (rlen != NULL)
		*rlen = larg;

	return (error);
}