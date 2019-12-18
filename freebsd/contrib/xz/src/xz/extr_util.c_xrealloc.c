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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  message_fatal (char*,int /*<<< orphan*/ ) ; 
 void* realloc (void*,size_t) ; 
 int /*<<< orphan*/  strerror (int const) ; 

extern void *
xrealloc(void *ptr, size_t size)
{
	assert(size > 0);

	// Save ptr so that we can free it if realloc fails.
	// The point is that message_fatal ends up calling stdio functions
	// which in some libc implementations might allocate memory from
	// the heap. Freeing ptr improves the chances that there's free
	// memory for stdio functions if they need it.
	void *p = ptr;
	ptr = realloc(ptr, size);

	if (ptr == NULL) {
		const int saved_errno = errno;
		free(p);
		message_fatal("%s", strerror(saved_errno));
	}

	return ptr;
}