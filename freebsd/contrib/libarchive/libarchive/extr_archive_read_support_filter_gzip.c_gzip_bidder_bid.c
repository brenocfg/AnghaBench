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

/* Variables and functions */
 scalar_t__ peek_at_header (struct archive_read_filter*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gzip_bidder_bid(struct archive_read_filter_bidder *self,
    struct archive_read_filter *filter)
{
	int bits_checked;

	(void)self; /* UNUSED */

	if (peek_at_header(filter, &bits_checked, NULL))
		return (bits_checked);
	return (0);
}