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
struct bhnd_nvram_iores {size_t size; size_t bus_width; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENXIO ; 
 size_t ummin (size_t,size_t) ; 

__attribute__((used)) static int
bhnd_nvram_iores_validate_req(struct bhnd_nvram_iores *iores, size_t offset,
    size_t *nbytes)
{
	/* Verify offset falls within the resource range */
	if (offset > iores->size)
		return (ENXIO);

	/* Check for eof */
	if (offset == iores->size) {
		*nbytes = 0;
		return (0);
	}

	/* Verify offset alignment */
	if (offset % iores->bus_width != 0)
		return (EFAULT);

	/* Limit nbytes to available range and verify size alignment */
	*nbytes = ummin(*nbytes, iores->size - offset);
	if (*nbytes < iores->bus_width && *nbytes % iores->bus_width != 0)
		return (EFAULT);

	return (0);
}