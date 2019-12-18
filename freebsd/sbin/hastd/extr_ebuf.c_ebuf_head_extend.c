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
struct ebuf {scalar_t__ eb_magic; unsigned char* eb_end; unsigned char* eb_start; unsigned char* eb_used; int /*<<< orphan*/  eb_size; } ;

/* Variables and functions */
 scalar_t__ EBUF_MAGIC ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  bcopy (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 
 unsigned char* malloc (size_t) ; 

__attribute__((used)) static int
ebuf_head_extend(struct ebuf *eb, size_t size)
{
	unsigned char *newstart, *newused;
	size_t newsize;

	PJDLOG_ASSERT(eb != NULL && eb->eb_magic == EBUF_MAGIC);

	newsize = eb->eb_end - eb->eb_start + (PAGE_SIZE / 4) + size;

	newstart = malloc(newsize);
	if (newstart == NULL)
		return (-1);
	newused =
	    newstart + (PAGE_SIZE / 4) + size + (eb->eb_used - eb->eb_start);

	bcopy(eb->eb_used, newused, eb->eb_size);

	eb->eb_start = newstart;
	eb->eb_used = newused;
	eb->eb_end = newstart + newsize;

	return (0);
}