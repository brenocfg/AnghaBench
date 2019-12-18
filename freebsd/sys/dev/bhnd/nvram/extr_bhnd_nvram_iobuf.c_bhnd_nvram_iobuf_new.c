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
struct bhnd_nvram_iobuf {int /*<<< orphan*/  size; int /*<<< orphan*/  buf; } ;
struct bhnd_nvram_io {int dummy; } ;

/* Variables and functions */
 struct bhnd_nvram_io* bhnd_nvram_iobuf_empty (size_t,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 

struct bhnd_nvram_io *
bhnd_nvram_iobuf_new(const void *buffer, size_t size)
{
	struct bhnd_nvram_io	*io;
	struct bhnd_nvram_iobuf	*iobuf;

	/* Allocate the iobuf */
	if ((io = bhnd_nvram_iobuf_empty(size, size)) == NULL)
		return (NULL);

	/* Copy the input to our new iobuf instance */
	iobuf = (struct bhnd_nvram_iobuf *)io;
	memcpy(iobuf->buf, buffer, iobuf->size);

	return (io);
}