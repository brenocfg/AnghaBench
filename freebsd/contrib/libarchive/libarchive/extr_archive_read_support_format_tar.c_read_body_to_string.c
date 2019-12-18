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
struct tar {int dummy; } ;
struct archive_string {char* s; size_t length; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;
struct archive_entry_header_ustar {int /*<<< orphan*/  size; } ;
typedef  int int64_t ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* __archive_read_ahead (struct archive_read*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * archive_string_ensure (struct archive_string*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,size_t) ; 
 int tar_atol (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tar_flush_unconsumed (struct archive_read*,size_t*) ; 

__attribute__((used)) static int
read_body_to_string(struct archive_read *a, struct tar *tar,
    struct archive_string *as, const void *h, size_t *unconsumed)
{
	int64_t size;
	const struct archive_entry_header_ustar *header;
	const void *src;

	(void)tar; /* UNUSED */
	header = (const struct archive_entry_header_ustar *)h;
	size  = tar_atol(header->size, sizeof(header->size));
	if ((size > 1048576) || (size < 0)) {
		archive_set_error(&a->archive, EINVAL,
		    "Special header too large");
		return (ARCHIVE_FATAL);
	}

	/* Fail if we can't make our buffer big enough. */
	if (archive_string_ensure(as, (size_t)size+1) == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "No memory");
		return (ARCHIVE_FATAL);
	}

	tar_flush_unconsumed(a, unconsumed);

	/* Read the body into the string. */
	*unconsumed = (size_t)((size + 511) & ~ 511);
	src = __archive_read_ahead(a, *unconsumed, NULL);
	if (src == NULL) {
		*unconsumed = 0;
		return (ARCHIVE_FATAL);
	}
	memcpy(as->s, src, (size_t)size);
	as->s[size] = '\0';
	as->length = (size_t)size;
	return (ARCHIVE_OK);
}