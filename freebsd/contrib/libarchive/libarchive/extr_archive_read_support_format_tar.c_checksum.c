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
struct archive_entry_header_ustar {char* checksum; } ;

/* Variables and functions */
 scalar_t__ tar_atol (char*,int) ; 

__attribute__((used)) static int
checksum(struct archive_read *a, const void *h)
{
	const unsigned char *bytes;
	const struct archive_entry_header_ustar	*header;
	int check, sum;
	size_t i;

	(void)a; /* UNUSED */
	bytes = (const unsigned char *)h;
	header = (const struct archive_entry_header_ustar *)h;

	/* Checksum field must hold an octal number */
	for (i = 0; i < sizeof(header->checksum); ++i) {
		char c = header->checksum[i];
		if (c != ' ' && c != '\0' && (c < '0' || c > '7'))
			return 0;
	}

	/*
	 * Test the checksum.  Note that POSIX specifies _unsigned_
	 * bytes for this calculation.
	 */
	sum = (int)tar_atol(header->checksum, sizeof(header->checksum));
	check = 0;
	for (i = 0; i < 148; i++)
		check += (unsigned char)bytes[i];
	for (; i < 156; i++)
		check += 32;
	for (; i < 512; i++)
		check += (unsigned char)bytes[i];
	if (sum == check)
		return (1);

	/*
	 * Repeat test with _signed_ bytes, just in case this archive
	 * was created by an old BSD, Solaris, or HP-UX tar with a
	 * broken checksum calculation.
	 */
	check = 0;
	for (i = 0; i < 148; i++)
		check += (signed char)bytes[i];
	for (; i < 156; i++)
		check += 32;
	for (; i < 512; i++)
		check += (signed char)bytes[i];
	if (sum == check)
		return (1);

	return (0);
}