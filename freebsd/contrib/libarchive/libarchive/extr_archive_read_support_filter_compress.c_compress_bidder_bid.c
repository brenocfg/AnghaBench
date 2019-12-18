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

__attribute__((used)) static int
compress_bidder_bid(struct archive_read_filter_bidder *self,
    struct archive_read_filter *filter)
{
	const unsigned char *buffer;
	ssize_t avail;
	int bits_checked;

	(void)self; /* UNUSED */

	/* Shortest valid compress file is 3 bytes. */
	buffer = __archive_read_filter_ahead(filter, 3, &avail);

	if (buffer == NULL)
		return (0);

	bits_checked = 0;
	/* First two bytes are the magic value */
	if (buffer[0] != 0x1F || buffer[1] != 0x9D)
		return (0);
	/* Third byte holds compression parameters. */
	if (buffer[2] & 0x20) /* Reserved bit, must be zero. */
		return (0);
	if (buffer[2] & 0x40) /* Reserved bit, must be zero. */
		return (0);
	bits_checked += 18;

	return (bits_checked);
}