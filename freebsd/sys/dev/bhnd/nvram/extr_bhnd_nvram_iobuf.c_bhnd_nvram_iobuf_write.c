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
struct bhnd_nvram_io {int dummy; } ;

/* Variables and functions */
 int bhnd_nvram_io_write_ptr (struct bhnd_nvram_io*,size_t,void**,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

__attribute__((used)) static int
bhnd_nvram_iobuf_write(struct bhnd_nvram_io *io, size_t offset,
    void *buffer, size_t nbytes)
{
	void	*ptr;
	int	 error;

	/* Try to fetch a direct pointer for at least nbytes */
	if ((error = bhnd_nvram_io_write_ptr(io, offset, &ptr, nbytes, NULL)))
		return (error);

	/* Copy in the provided data */
	memcpy(ptr, buffer, nbytes);
	return (0);
}