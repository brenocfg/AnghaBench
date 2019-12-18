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
struct memdata {struct memblock* last; struct memblock* first; } ;
struct memblock {size_t size; struct memblock* next; scalar_t__ buff; int /*<<< orphan*/  filebytes; } ;
struct archive {int dummy; } ;
typedef  long ssize_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ filedata ; 
 int filedatasize ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,size_t) ; 
 int /*<<< orphan*/  memset (struct memblock*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t
memory_write(struct archive *a, void *_private, const void *buff, size_t size)
{
	struct memdata *private = _private;
	struct memblock *block;

	(void)a;

	/*
	 * Since libarchive tries to behave in a zero-copy manner, if
	 * you give a pointer to filedata to the library, a pointer
	 * into that data will (usually) pop out here.  This way, we
	 * can tell the difference between filedata and library header
	 * and metadata.
	 */
	if ((const char *)filedata <= (const char *)buff
	    && (const char *)buff < (const char *)filedata + filedatasize) {
		/* We don't need to store a block of file data. */
		private->last->filebytes += (int64_t)size;
	} else {
		/* Yes, we're assuming the very first write is metadata. */
		/* It's header or metadata, copy and save it. */
		block = (struct memblock *)malloc(sizeof(*block));
		memset(block, 0, sizeof(*block));
		block->size = size;
		block->buff = malloc(size);
		memcpy(block->buff, buff, size);
		if (private->last == NULL) {
			private->first = private->last = block;
		} else {
			private->last->next = block;
			private->last = block;
		}
		block->next = NULL;
	}
	return ((long)size);
}