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
struct archive_string {char* s; size_t buffer_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  archive_string_free (struct archive_string*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ realloc (char*,size_t) ; 

struct archive_string *
archive_string_ensure(struct archive_string *as, size_t s)
{
	char *p;
	size_t new_length;

	/* If buffer is already big enough, don't reallocate. */
	if (as->s && (s <= as->buffer_length))
		return (as);

	/*
	 * Growing the buffer at least exponentially ensures that
	 * append operations are always linear in the number of
	 * characters appended.  Using a smaller growth rate for
	 * larger buffers reduces memory waste somewhat at the cost of
	 * a larger constant factor.
	 */
	if (as->buffer_length < 32)
		/* Start with a minimum 32-character buffer. */
		new_length = 32;
	else if (as->buffer_length < 8192)
		/* Buffers under 8k are doubled for speed. */
		new_length = as->buffer_length + as->buffer_length;
	else {
		/* Buffers 8k and over grow by at least 25% each time. */
		new_length = as->buffer_length + as->buffer_length / 4;
		/* Be safe: If size wraps, fail. */
		if (new_length < as->buffer_length) {
			/* On failure, wipe the string and return NULL. */
			archive_string_free(as);
			errno = ENOMEM;/* Make sure errno has ENOMEM. */
			return (NULL);
		}
	}
	/*
	 * The computation above is a lower limit to how much we'll
	 * grow the buffer.  In any case, we have to grow it enough to
	 * hold the request.
	 */
	if (new_length < s)
		new_length = s;
	/* Now we can reallocate the buffer. */
	p = (char *)realloc(as->s, new_length);
	if (p == NULL) {
		/* On failure, wipe the string and return NULL. */
		archive_string_free(as);
		errno = ENOMEM;/* Make sure errno has ENOMEM. */
		return (NULL);
	}

	as->s = p;
	as->buffer_length = new_length;
	return (as);
}