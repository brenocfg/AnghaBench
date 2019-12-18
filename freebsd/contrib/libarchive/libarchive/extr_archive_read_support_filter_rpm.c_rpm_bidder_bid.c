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
rpm_bidder_bid(struct archive_read_filter_bidder *self,
    struct archive_read_filter *filter)
{
	const unsigned char *b;
	ssize_t avail;
	int bits_checked;

	(void)self; /* UNUSED */

	b = __archive_read_filter_ahead(filter, 8, &avail);
	if (b == NULL)
		return (0);

	bits_checked = 0;
	/*
	 * Verify Header Magic Bytes : 0XED 0XAB 0XEE 0XDB
	 */
	if (memcmp(b, "\xED\xAB\xEE\xDB", 4) != 0)
		return (0);
	bits_checked += 32;
	/*
	 * Check major version.
	 */
	if (b[4] != 3 && b[4] != 4)
		return (0);
	bits_checked += 8;
	/*
	 * Check package type; binary or source.
	 */
	if (b[6] != 0)
		return (0);
	bits_checked += 8;
	if (b[7] != 0 && b[7] != 1)
		return (0);
	bits_checked += 8;

	return (bits_checked);
}