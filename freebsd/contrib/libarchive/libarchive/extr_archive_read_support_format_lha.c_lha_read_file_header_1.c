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
struct lha {unsigned char header_size; size_t compsize; int /*<<< orphan*/  setflag; int /*<<< orphan*/  crc; int /*<<< orphan*/  filename; int /*<<< orphan*/  mtime; void* origsize; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  CRC_IS_SET ; 
 int H1_COMP_SIZE_OFFSET ; 
 int H1_DOS_TIME_OFFSET ; 
 int H1_FILE_NAME_OFFSET ; 
 int H1_FIXED_SIZE ; 
 size_t H1_HEADER_SIZE_OFFSET ; 
 size_t H1_HEADER_SUM_OFFSET ; 
 size_t H1_NAME_LEN_OFFSET ; 
 int H1_ORIG_SIZE_OFFSET ; 
 unsigned char* __archive_read_ahead (struct archive_read*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __archive_read_consume (struct archive_read*,int) ; 
 int /*<<< orphan*/  archive_le16dec (unsigned char const*) ; 
 void* archive_le32dec (unsigned char const*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_strncpy (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 unsigned char lha_calcsum (int /*<<< orphan*/ ,unsigned char const*,int,int) ; 
 int /*<<< orphan*/  lha_dos_time (unsigned char const*) ; 
 int lha_read_file_extended_header (struct archive_read*,struct lha*,int /*<<< orphan*/ *,int,size_t,size_t*) ; 
 int truncated_error (struct archive_read*) ; 

__attribute__((used)) static int
lha_read_file_header_1(struct archive_read *a, struct lha *lha)
{
	const unsigned char *p;
	size_t extdsize;
	int i, err, err2;
	int namelen, padding;
	unsigned char headersum, sum_calculated;

	err = ARCHIVE_OK;

	if ((p = __archive_read_ahead(a, H1_FIXED_SIZE, NULL)) == NULL)
		return (truncated_error(a));

	lha->header_size = p[H1_HEADER_SIZE_OFFSET] + 2;
	headersum = p[H1_HEADER_SUM_OFFSET];
	/* Note: An extended header size is included in a compsize. */
	lha->compsize = archive_le32dec(p + H1_COMP_SIZE_OFFSET);
	lha->origsize = archive_le32dec(p + H1_ORIG_SIZE_OFFSET);
	lha->mtime = lha_dos_time(p + H1_DOS_TIME_OFFSET);
	namelen = p[H1_NAME_LEN_OFFSET];
	/* Calculate a padding size. The result will be normally 0 only(?) */
	padding = ((int)lha->header_size) - H1_FIXED_SIZE - namelen;

	if (namelen > 230 || padding < 0)
		goto invalid;

	if ((p = __archive_read_ahead(a, lha->header_size, NULL)) == NULL)
		return (truncated_error(a));

	for (i = 0; i < namelen; i++) {
		if (p[i + H1_FILE_NAME_OFFSET] == 0xff)
			goto invalid;/* Invalid filename. */
	}
	archive_strncpy(&lha->filename, p + H1_FILE_NAME_OFFSET, namelen);
	lha->crc = archive_le16dec(p + H1_FILE_NAME_OFFSET + namelen);
	lha->setflag |= CRC_IS_SET;

	sum_calculated = lha_calcsum(0, p, 2, lha->header_size - 2);
	/* Consume used bytes but not include `next header size' data
	 * since it will be consumed in lha_read_file_extended_header(). */
	__archive_read_consume(a, lha->header_size - 2);

	/* Read extended headers */
	err2 = lha_read_file_extended_header(a, lha, NULL, 2,
	    (size_t)(lha->compsize + 2), &extdsize);
	if (err2 < ARCHIVE_WARN)
		return (err2);
	if (err2 < err)
		err = err2;
	/* Get a real compressed file size. */
	lha->compsize -= extdsize - 2;

	if (lha->compsize < 0)
		goto invalid;	/* Invalid compressed file size */

	if (sum_calculated != headersum) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "LHa header sum error");
		return (ARCHIVE_FATAL);
	}
	return (err);
invalid:
	archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
	    "Invalid LHa header");
	return (ARCHIVE_FATAL);
}