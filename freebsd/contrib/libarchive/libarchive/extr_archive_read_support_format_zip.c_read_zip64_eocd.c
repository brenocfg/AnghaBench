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
struct zip {scalar_t__ central_directory_offset; } ;
struct archive_read {int dummy; } ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 char* __archive_read_ahead (struct archive_read*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ __archive_read_seek (struct archive_read*,int,int /*<<< orphan*/ ) ; 
 int archive_le32dec (char const*) ; 
 scalar_t__ archive_le64dec (char const*) ; 

__attribute__((used)) static int
read_zip64_eocd(struct archive_read *a, struct zip *zip, const char *p)
{
	int64_t eocd64_offset;
	int64_t eocd64_size;

	/* Sanity-check the locator record. */

	/* Central dir must be on first volume. */
	if (archive_le32dec(p + 4) != 0)
		return 0;
	/* Must be only a single volume. */
	if (archive_le32dec(p + 16) != 1)
		return 0;

	/* Find the Zip64 EOCD record. */
	eocd64_offset = archive_le64dec(p + 8);
	if (__archive_read_seek(a, eocd64_offset, SEEK_SET) < 0)
		return 0;
	if ((p = __archive_read_ahead(a, 56, NULL)) == NULL)
		return 0;
	/* Make sure we can read all of it. */
	eocd64_size = archive_le64dec(p + 4) + 12;
	if (eocd64_size < 56 || eocd64_size > 16384)
		return 0;
	if ((p = __archive_read_ahead(a, (size_t)eocd64_size, NULL)) == NULL)
		return 0;

	/* Sanity-check the EOCD64 */
	if (archive_le32dec(p + 16) != 0) /* Must be disk #0 */
		return 0;
	if (archive_le32dec(p + 20) != 0) /* CD must be on disk #0 */
		return 0;
	/* CD can't be split. */
	if (archive_le64dec(p + 24) != archive_le64dec(p + 32))
		return 0;

	/* Save the central directory offset for later use. */
	zip->central_directory_offset = archive_le64dec(p + 48);

	return 32;
}