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
struct bhnd_nvram_iobuf {size_t capacity; size_t size; } ;
struct bhnd_nvram_io {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 

__attribute__((used)) static int
bhnd_nvram_iobuf_setsize(struct bhnd_nvram_io *io, size_t size)
{
	struct bhnd_nvram_iobuf	*iobuf = (struct bhnd_nvram_iobuf *)io;

	/* Can't exceed the actual capacity */
	if (size > iobuf->capacity)
		return (ENXIO);

	iobuf->size = size;
	return (0);
}