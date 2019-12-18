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
struct archive_read {int dummy; } ;
struct archive_entry_header_ustar {char* typeflag; int /*<<< orphan*/  rdevminor; int /*<<< orphan*/  rdevmajor; int /*<<< orphan*/  size; int /*<<< orphan*/  mtime; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  mode; int /*<<< orphan*/  version; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 char* __archive_read_ahead (struct archive_read*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ archive_block_is_null (char const*) ; 
 int /*<<< orphan*/  checksum (struct archive_read*,char const*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ validate_number_field (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
archive_read_format_tar_bid(struct archive_read *a, int best_bid)
{
	int bid;
	const char *h;
	const struct archive_entry_header_ustar *header;

	(void)best_bid; /* UNUSED */

	bid = 0;

	/* Now let's look at the actual header and see if it matches. */
	h = __archive_read_ahead(a, 512, NULL);
	if (h == NULL)
		return (-1);

	/* If it's an end-of-archive mark, we can handle it. */
	if (h[0] == 0 && archive_block_is_null(h)) {
		/*
		 * Usually, I bid the number of bits verified, but
		 * in this case, 4096 seems excessive so I picked 10 as
		 * an arbitrary but reasonable-seeming value.
		 */
		return (10);
	}

	/* If it's not an end-of-archive mark, it must have a valid checksum.*/
	if (!checksum(a, h))
		return (0);
	bid += 48;  /* Checksum is usually 6 octal digits. */

	header = (const struct archive_entry_header_ustar *)h;

	/* Recognize POSIX formats. */
	if ((memcmp(header->magic, "ustar\0", 6) == 0)
	    && (memcmp(header->version, "00", 2) == 0))
		bid += 56;

	/* Recognize GNU tar format. */
	if ((memcmp(header->magic, "ustar ", 6) == 0)
	    && (memcmp(header->version, " \0", 2) == 0))
		bid += 56;

	/* Type flag must be null, digit or A-Z, a-z. */
	if (header->typeflag[0] != 0 &&
	    !( header->typeflag[0] >= '0' && header->typeflag[0] <= '9') &&
	    !( header->typeflag[0] >= 'A' && header->typeflag[0] <= 'Z') &&
	    !( header->typeflag[0] >= 'a' && header->typeflag[0] <= 'z') )
		return (0);
	bid += 2;  /* 6 bits of variation in an 8-bit field leaves 2 bits. */

	/*
	 * Check format of mode/uid/gid/mtime/size/rdevmajor/rdevminor fields.
	 */
	if (bid > 0 && (
	    validate_number_field(header->mode, sizeof(header->mode)) == 0
	    || validate_number_field(header->uid, sizeof(header->uid)) == 0
	    || validate_number_field(header->gid, sizeof(header->gid)) == 0
	    || validate_number_field(header->mtime, sizeof(header->mtime)) == 0
	    || validate_number_field(header->size, sizeof(header->size)) == 0
	    || validate_number_field(header->rdevmajor, sizeof(header->rdevmajor)) == 0
	    || validate_number_field(header->rdevminor, sizeof(header->rdevminor)) == 0)) {
		bid = 0;
	}

	return (bid);
}