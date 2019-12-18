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
xz_bidder_bid(struct archive_read_filter_bidder *self,
    struct archive_read_filter *filter)
{
	const unsigned char *buffer;
	ssize_t avail;

	(void)self; /* UNUSED */

	buffer = __archive_read_filter_ahead(filter, 6, &avail);
	if (buffer == NULL)
		return (0);

	/*
	 * Verify Header Magic Bytes : FD 37 7A 58 5A 00
	 */
	if (memcmp(buffer, "\xFD\x37\x7A\x58\x5A\x00", 6) != 0)
		return (0);

	return (48);
}