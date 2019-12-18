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
typedef  int /*<<< orphan*/  uint8_t ;
struct bhnd_nvram_iobuf {size_t size; scalar_t__ buf; } ;

/* Variables and functions */
 int ENXIO ; 

__attribute__((used)) static int
bhnd_nvram_iobuf_ptr(struct bhnd_nvram_iobuf *iobuf, size_t offset, void **ptr,
    size_t nbytes, size_t *navail)
{
	size_t avail;

	/* Verify offset+nbytes fall within the buffer range */
	if (offset > iobuf->size)
		return (ENXIO);

	avail = iobuf->size - offset;
	if (avail < nbytes)
		return (ENXIO);

	/* Valid I/O range, provide a pointer to the buffer and the
	 * total count of available bytes */
	*ptr = ((uint8_t *)iobuf->buf) + offset;
	if (navail != NULL)
		*navail = avail;

	return (0);
}