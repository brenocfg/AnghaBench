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
 int /*<<< orphan*/  LRZIP_HEADER_MAGIC ; 
 size_t LRZIP_HEADER_MAGIC_LEN ; 
 unsigned char* __archive_read_filter_ahead (struct archive_read_filter*,scalar_t__,scalar_t__*) ; 
 scalar_t__ memcmp (unsigned char const*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
lrzip_bidder_bid(struct archive_read_filter_bidder *self,
    struct archive_read_filter *filter)
{
	const unsigned char *p;
	ssize_t avail, len;
	int i;

	(void)self; /* UNUSED */
	/* Start by looking at the first six bytes of the header, which
	 * is all fixed layout. */
	len = 6;
	p = __archive_read_filter_ahead(filter, len, &avail);
	if (p == NULL || avail == 0)
		return (0);

	if (memcmp(p, LRZIP_HEADER_MAGIC, LRZIP_HEADER_MAGIC_LEN))
		return (0);

	/* current major version is always 0, verify this */
	if (p[LRZIP_HEADER_MAGIC_LEN])
		return 0;
	/* support only v0.6+ lrzip for sanity */
	i = p[LRZIP_HEADER_MAGIC_LEN + 1];
	if ((i < 6) || (i > 10))
		return 0;

	return (int)len;
}