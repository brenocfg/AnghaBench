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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  size ;

/* Variables and functions */
 int /*<<< orphan*/  allzeros (unsigned char const*,size_t) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  pjdlog_warning (char*,size_t) ; 

__attribute__((used)) static void *
hast_hole_compress(const unsigned char *data, size_t *sizep)
{
	uint32_t size;
	void *newbuf;

	if (!allzeros(data, *sizep))
		return (NULL);

	newbuf = malloc(sizeof(size));
	if (newbuf == NULL) {
		pjdlog_warning("Unable to compress (no memory: %zu).",
		    (size_t)*sizep);
		return (NULL);
	}
	size = htole32((uint32_t)*sizep);
	bcopy(&size, newbuf, sizeof(size));
	*sizep = sizeof(size);

	return (newbuf);
}