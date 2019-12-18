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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  size ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (unsigned char const*,size_t*,int) ; 
 int /*<<< orphan*/  bzero (void*,size_t) ; 
 size_t le32toh (size_t) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  pjdlog_error (char*,size_t) ; 

__attribute__((used)) static void *
hast_hole_decompress(const unsigned char *data, size_t *sizep)
{
	uint32_t size;
	void *newbuf;

	if (*sizep != sizeof(size)) {
		pjdlog_error("Unable to decompress (invalid size: %zu).",
		    *sizep);
		return (NULL);
	}

	bcopy(data, &size, sizeof(size));
	size = le32toh(size);

	newbuf = malloc(size);
	if (newbuf == NULL) {
		pjdlog_error("Unable to decompress (no memory: %zu).",
		    (size_t)size);
		return (NULL);
	}
	bzero(newbuf, size);
	*sizep = size;

	return (newbuf);
}