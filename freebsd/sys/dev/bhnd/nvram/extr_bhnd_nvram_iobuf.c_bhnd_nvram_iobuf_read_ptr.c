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
struct bhnd_nvram_iobuf {int dummy; } ;
struct bhnd_nvram_io {int dummy; } ;

/* Variables and functions */
 int bhnd_nvram_iobuf_ptr (struct bhnd_nvram_iobuf*,size_t,void**,size_t,size_t*) ; 

__attribute__((used)) static int
bhnd_nvram_iobuf_read_ptr(struct bhnd_nvram_io *io, size_t offset,
    const void **ptr, size_t nbytes, size_t *navail)
{
	struct bhnd_nvram_iobuf	*iobuf;
	void			*ioptr;
	int			 error;

	iobuf = (struct bhnd_nvram_iobuf *) io;

	/* Return a pointer into our backing buffer */
	error = bhnd_nvram_iobuf_ptr(iobuf, offset, &ioptr, nbytes, navail);
	if (error)
		return (error);

	*ptr = ioptr;

	return (0);
}