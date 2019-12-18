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
struct bhnd_nvram_ioptr {int flags; size_t capacity; size_t size; } ;
struct bhnd_nvram_io {int dummy; } ;

/* Variables and functions */
 int BHND_NVRAM_IOPTR_RDWR ; 
 int ENODEV ; 
 int ENXIO ; 

__attribute__((used)) static int
bhnd_nvram_ioptr_setsize(struct bhnd_nvram_io *io, size_t size)
{
	struct bhnd_nvram_ioptr	*ioptr = (struct bhnd_nvram_ioptr *)io;

	/* Must be writable */
	if (!(ioptr->flags & BHND_NVRAM_IOPTR_RDWR))
		return (ENODEV);
	
	/* Can't exceed the actual capacity */
	if (size > ioptr->capacity)
		return (ENXIO);
	
	ioptr->size = size;
	return (0);
}