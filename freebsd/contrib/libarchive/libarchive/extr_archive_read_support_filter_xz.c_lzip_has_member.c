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
struct archive_read_filter {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 unsigned char* __archive_read_filter_ahead (struct archive_read_filter*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (unsigned char const*,char*,int) ; 

__attribute__((used)) static int
lzip_has_member(struct archive_read_filter *filter)
{
	const unsigned char *buffer;
	ssize_t avail;
	int bits_checked;
	int log2dic;

	buffer = __archive_read_filter_ahead(filter, 6, &avail);
	if (buffer == NULL)
		return (0);

	/*
	 * Verify Header Magic Bytes : 4C 5A 49 50 (`LZIP')
	 */
	bits_checked = 0;
	if (memcmp(buffer, "LZIP", 4) != 0)
		return (0);
	bits_checked += 32;

	/* A version number must be 0 or 1 */
	if (buffer[4] != 0 && buffer[4] != 1)
		return (0);
	bits_checked += 8;

	/* Dictionary size. */
	log2dic = buffer[5] & 0x1f;
	if (log2dic < 12 || log2dic > 27)
		return (0);
	bits_checked += 8;

	return (bits_checked);
}