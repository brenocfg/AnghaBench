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
struct bhnd_nvram_io {int /*<<< orphan*/ * iops; } ;
struct bhnd_nvram_iobuf {size_t size; size_t capacity; struct bhnd_nvram_io io; int /*<<< orphan*/ * buf; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int SIZE_MAX ; 
 int /*<<< orphan*/  bhnd_nv_free (struct bhnd_nvram_iobuf*) ; 
 void* bhnd_nv_malloc (size_t) ; 
 int /*<<< orphan*/  bhnd_nvram_iobuf_ops ; 

struct bhnd_nvram_io *
bhnd_nvram_iobuf_empty(size_t size, size_t capacity)
{
	struct bhnd_nvram_iobuf	*iobuf;
	size_t			 iosz;
	bool			 inline_alloc;

	/* Sanity check the capacity */
	if (size > capacity)
		return (NULL);

	/* Would sizeof(iobuf)+capacity overflow? */
	if (SIZE_MAX - sizeof(*iobuf) < capacity) {
		inline_alloc = false;
		iosz = sizeof(*iobuf);
	} else {
		inline_alloc = true;
		iosz = sizeof(*iobuf) + capacity;
	}

	/* Allocate I/O context */
	iobuf = bhnd_nv_malloc(iosz);
	if (iobuf == NULL)
		return (NULL);

	iobuf->io.iops = &bhnd_nvram_iobuf_ops;
	iobuf->buf = NULL;
	iobuf->size = size;
	iobuf->capacity = capacity;

	/* Either allocate our backing buffer, or initialize the
	 * backing buffer with a reference to our inline allocation. */
	if (inline_alloc)
		iobuf->buf = &iobuf->data;
	else
		iobuf->buf = bhnd_nv_malloc(iobuf->capacity);


	if (iobuf->buf == NULL) {
		bhnd_nv_free(iobuf);
		return (NULL);
	}

	return (&iobuf->io);
}