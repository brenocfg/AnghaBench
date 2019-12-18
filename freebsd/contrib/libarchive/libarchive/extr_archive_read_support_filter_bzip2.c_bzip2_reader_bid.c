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
struct archive_read_filter_bidder {int dummy; } ;
struct archive_read_filter {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 unsigned char* __archive_read_filter_ahead (struct archive_read_filter*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (unsigned char const*,char*,int) ; 

__attribute__((used)) static int
bzip2_reader_bid(struct archive_read_filter_bidder *self, struct archive_read_filter *filter)
{
	const unsigned char *buffer;
	ssize_t avail;
	int bits_checked;

	(void)self; /* UNUSED */

	/* Minimal bzip2 archive is 14 bytes. */
	buffer = __archive_read_filter_ahead(filter, 14, &avail);
	if (buffer == NULL)
		return (0);

	/* First three bytes must be "BZh" */
	bits_checked = 0;
	if (memcmp(buffer, "BZh", 3) != 0)
		return (0);
	bits_checked += 24;

	/* Next follows a compression flag which must be an ASCII digit. */
	if (buffer[3] < '1' || buffer[3] > '9')
		return (0);
	bits_checked += 5;

	/* After BZh[1-9], there must be either a data block
	 * which begins with 0x314159265359 or an end-of-data
	 * marker of 0x177245385090. */
	if (memcmp(buffer + 4, "\x31\x41\x59\x26\x53\x59", 6) == 0)
		bits_checked += 48;
	else if (memcmp(buffer + 4, "\x17\x72\x45\x38\x50\x90", 6) == 0)
		bits_checked += 48;
	else
		return (0);

	return (bits_checked);
}