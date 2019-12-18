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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  LZOP_HEADER_MAGIC ; 
 int LZOP_HEADER_MAGIC_LEN ; 
 unsigned char* __archive_read_filter_ahead (struct archive_read_filter*,int,scalar_t__*) ; 
 scalar_t__ memcmp (unsigned char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lzop_bidder_bid(struct archive_read_filter_bidder *self,
    struct archive_read_filter *filter)
{
	const unsigned char *p;
	ssize_t avail;

	(void)self; /* UNUSED */

	p = __archive_read_filter_ahead(filter, LZOP_HEADER_MAGIC_LEN, &avail);
	if (p == NULL || avail == 0)
		return (0);

	if (memcmp(p, LZOP_HEADER_MAGIC, LZOP_HEADER_MAGIC_LEN))
		return (0);

	return (LZOP_HEADER_MAGIC_LEN * 8);
}