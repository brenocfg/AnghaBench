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
struct bhnd_nvram_ioptr {int dummy; } ;
struct bhnd_nvram_io {int dummy; } ;

/* Variables and functions */
 int bhnd_nvram_ioptr_ptr (struct bhnd_nvram_ioptr*,size_t,void**,size_t,size_t*) ; 

__attribute__((used)) static int
bhnd_nvram_ioptr_read_ptr(struct bhnd_nvram_io *io, size_t offset,
			  const void **ptr, size_t nbytes, size_t *navail)
{
	struct bhnd_nvram_ioptr	*ioptr;
	void			*writep;
	int			 error;
	
	ioptr = (struct bhnd_nvram_ioptr *) io;
	
	/* Return a pointer into our backing buffer */
	error = bhnd_nvram_ioptr_ptr(ioptr, offset, &writep, nbytes, navail);
	if (error)
		return (error);
	
	*ptr = writep;
	
	return (0);
}