#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {unsigned int length; char* s; } ;
struct lha {int header_crc; unsigned char dos_attr; size_t birthtime; size_t mtime; size_t atime; int setflag; int mode; int gid; int uid; TYPE_1__ uname; TYPE_1__ gname; int /*<<< orphan*/ * sconv; void* origsize; void* compsize; int /*<<< orphan*/  atime_tv_nsec; int /*<<< orphan*/  mtime_tv_nsec; int /*<<< orphan*/  birthtime_tv_nsec; TYPE_1__ dirname; TYPE_1__ filename; } ;
struct archive_string {char* s; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;
typedef  int mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ATIME_IS_SET ; 
 int BIRTHTIME_IS_SET ; 
#define  EXT_CODEPAGE 144 
#define  EXT_DIRECTORY 143 
#define  EXT_DOS_ATTR 142 
#define  EXT_FILENAME 141 
#define  EXT_FILESIZE 140 
#define  EXT_HEADER_CRC 139 
#define  EXT_NEW_ATTR 138 
#define  EXT_OS2_NEW_ATTR 137 
#define  EXT_TIMESTAMP 136 
#define  EXT_TIMEZONE 135 
#define  EXT_UNIX_GID_UID 134 
#define  EXT_UNIX_GNAME 133 
#define  EXT_UNIX_MODE 132 
#define  EXT_UNIX_MTIME 131 
#define  EXT_UNIX_UNAME 130 
#define  EXT_UTF16_DIRECTORY 129 
#define  EXT_UTF16_FILENAME 128 
 int UNIX_MODE_IS_SET ; 
 void* __archive_read_ahead (struct archive_read*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __archive_read_consume (struct archive_read*,size_t) ; 
 int archive_le16dec (unsigned char const*) ; 
 size_t archive_le32dec (unsigned char const*) ; 
 void* archive_le64dec (unsigned char const*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * archive_string_conversion_from_charset (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  archive_string_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  archive_string_free (struct archive_string*) ; 
 int /*<<< orphan*/  archive_string_init (struct archive_string*) ; 
 int /*<<< orphan*/  archive_string_sprintf (struct archive_string*,char*,int) ; 
 int /*<<< orphan*/  archive_strncpy (TYPE_1__*,char const*,size_t) ; 
 int /*<<< orphan*/  lha_crc16 (int /*<<< orphan*/ ,...) ; 
 void* lha_win_time (void*,int /*<<< orphan*/ *) ; 
 int truncated_error (struct archive_read*) ; 

__attribute__((used)) static int
lha_read_file_extended_header(struct archive_read *a, struct lha *lha,
    uint16_t *crc, int sizefield_length, size_t limitsize, size_t *total_size)
{
	const void *h;
	const unsigned char *extdheader;
	size_t	extdsize;
	size_t	datasize;
	unsigned int i;
	unsigned char extdtype;

#define EXT_HEADER_CRC		0x00		/* Header CRC and information*/
#define EXT_FILENAME		0x01		/* Filename 		    */
#define EXT_DIRECTORY		0x02		/* Directory name	    */
#define EXT_DOS_ATTR		0x40		/* MS-DOS attribute	    */
#define EXT_TIMESTAMP		0x41		/* Windows time stamp	    */
#define EXT_FILESIZE		0x42		/* Large file size	    */
#define EXT_TIMEZONE		0x43		/* Time zone		    */
#define EXT_UTF16_FILENAME	0x44		/* UTF-16 filename 	    */
#define EXT_UTF16_DIRECTORY	0x45		/* UTF-16 directory name    */
#define EXT_CODEPAGE		0x46		/* Codepage		    */
#define EXT_UNIX_MODE		0x50		/* File permission	    */
#define EXT_UNIX_GID_UID	0x51		/* gid,uid		    */
#define EXT_UNIX_GNAME		0x52		/* Group name		    */
#define EXT_UNIX_UNAME		0x53		/* User name		    */
#define EXT_UNIX_MTIME		0x54		/* Modified time	    */
#define EXT_OS2_NEW_ATTR	0x7f		/* new attribute(OS/2 only) */
#define EXT_NEW_ATTR		0xff		/* new attribute	    */

	*total_size = sizefield_length;

	for (;;) {
		/* Read an extended header size. */
		if ((h =
		    __archive_read_ahead(a, sizefield_length, NULL)) == NULL)
			return (truncated_error(a));
		/* Check if the size is the zero indicates the end of the
		 * extended header. */
		if (sizefield_length == sizeof(uint16_t))
			extdsize = archive_le16dec(h);
		else
			extdsize = archive_le32dec(h);
		if (extdsize == 0) {
			/* End of extended header */
			if (crc != NULL)
				*crc = lha_crc16(*crc, h, sizefield_length);
			__archive_read_consume(a, sizefield_length);
			return (ARCHIVE_OK);
		}

		/* Sanity check to the extended header size. */
		if (((uint64_t)*total_size + extdsize) >
				    (uint64_t)limitsize ||
		    extdsize <= (size_t)sizefield_length)
			goto invalid;

		/* Read the extended header. */
		if ((h = __archive_read_ahead(a, extdsize, NULL)) == NULL)
			return (truncated_error(a));
		*total_size += extdsize;

		extdheader = (const unsigned char *)h;
		/* Get the extended header type. */
		extdtype = extdheader[sizefield_length];
		/* Calculate an extended data size. */
		datasize = extdsize - (1 + sizefield_length);
		/* Skip an extended header size field and type field. */
		extdheader += sizefield_length + 1;

		if (crc != NULL && extdtype != EXT_HEADER_CRC)
			*crc = lha_crc16(*crc, h, extdsize);
		switch (extdtype) {
		case EXT_HEADER_CRC:
			/* We only use a header CRC. Following data will not
			 * be used. */
			if (datasize >= 2) {
				lha->header_crc = archive_le16dec(extdheader);
				if (crc != NULL) {
					static const char zeros[2] = {0, 0};
					*crc = lha_crc16(*crc, h,
					    extdsize - datasize);
					/* CRC value itself as zero */
					*crc = lha_crc16(*crc, zeros, 2);
					*crc = lha_crc16(*crc,
					    extdheader+2, datasize - 2);
				}
			}
			break;
		case EXT_FILENAME:
			if (datasize == 0) {
				/* maybe directory header */
				archive_string_empty(&lha->filename);
				break;
			}
			if (extdheader[0] == '\0')
				goto invalid;
			archive_strncpy(&lha->filename,
			    (const char *)extdheader, datasize);
			break;
		case EXT_DIRECTORY:
			if (datasize == 0 || extdheader[0] == '\0')
				/* no directory name data. exit this case. */
				goto invalid;

			archive_strncpy(&lha->dirname,
		  	    (const char *)extdheader, datasize);
			/*
			 * Convert directory delimiter from 0xFF
			 * to '/' for local system.
	 		 */
			for (i = 0; i < lha->dirname.length; i++) {
				if ((unsigned char)lha->dirname.s[i] == 0xFF)
					lha->dirname.s[i] = '/';
			}
			/* Is last character directory separator? */
			if (lha->dirname.s[lha->dirname.length-1] != '/')
				/* invalid directory data */
				goto invalid;
			break;
		case EXT_DOS_ATTR:
			if (datasize == 2)
				lha->dos_attr = (unsigned char)
				    (archive_le16dec(extdheader) & 0xff);
			break;
		case EXT_TIMESTAMP:
			if (datasize == (sizeof(uint64_t) * 3)) {
				lha->birthtime = lha_win_time(
				    archive_le64dec(extdheader),
				    &lha->birthtime_tv_nsec);
				extdheader += sizeof(uint64_t);
				lha->mtime = lha_win_time(
				    archive_le64dec(extdheader),
				    &lha->mtime_tv_nsec);
				extdheader += sizeof(uint64_t);
				lha->atime = lha_win_time(
				    archive_le64dec(extdheader),
				    &lha->atime_tv_nsec);
				lha->setflag |= BIRTHTIME_IS_SET |
				    ATIME_IS_SET;
			}
			break;
		case EXT_FILESIZE:
			if (datasize == sizeof(uint64_t) * 2) {
				lha->compsize = archive_le64dec(extdheader);
				extdheader += sizeof(uint64_t);
				lha->origsize = archive_le64dec(extdheader);
			}
			break;
		case EXT_CODEPAGE:
			/* Get an archived filename charset from codepage.
			 * This overwrites the charset specified by
			 * hdrcharset option. */
			if (datasize == sizeof(uint32_t)) {
				struct archive_string cp;
				const char *charset;

				archive_string_init(&cp);
				switch (archive_le32dec(extdheader)) {
				case 65001: /* UTF-8 */
					charset = "UTF-8";
					break;
				default:
					archive_string_sprintf(&cp, "CP%d",
					    (int)archive_le32dec(extdheader));
					charset = cp.s;
					break;
				}
				lha->sconv =
				    archive_string_conversion_from_charset(
					&(a->archive), charset, 1);
				archive_string_free(&cp);
				if (lha->sconv == NULL)
					return (ARCHIVE_FATAL);
			}
			break;
		case EXT_UNIX_MODE:
			if (datasize == sizeof(uint16_t)) {
				lha->mode = archive_le16dec(extdheader);
				lha->setflag |= UNIX_MODE_IS_SET;
			}
			break;
		case EXT_UNIX_GID_UID:
			if (datasize == (sizeof(uint16_t) * 2)) {
				lha->gid = archive_le16dec(extdheader);
				lha->uid = archive_le16dec(extdheader+2);
			}
			break;
		case EXT_UNIX_GNAME:
			if (datasize > 0)
				archive_strncpy(&lha->gname,
				    (const char *)extdheader, datasize);
			break;
		case EXT_UNIX_UNAME:
			if (datasize > 0)
				archive_strncpy(&lha->uname,
				    (const char *)extdheader, datasize);
			break;
		case EXT_UNIX_MTIME:
			if (datasize == sizeof(uint32_t))
				lha->mtime = archive_le32dec(extdheader);
			break;
		case EXT_OS2_NEW_ATTR:
			/* This extended header is OS/2 depend. */
			if (datasize == 16) {
				lha->dos_attr = (unsigned char)
				    (archive_le16dec(extdheader) & 0xff);
				lha->mode = archive_le16dec(extdheader+2);
				lha->gid = archive_le16dec(extdheader+4);
				lha->uid = archive_le16dec(extdheader+6);
				lha->birthtime = archive_le32dec(extdheader+8);
				lha->atime = archive_le32dec(extdheader+12);
				lha->setflag |= UNIX_MODE_IS_SET
				    | BIRTHTIME_IS_SET | ATIME_IS_SET;
			}
			break;
		case EXT_NEW_ATTR:
			if (datasize == 20) {
				lha->mode = (mode_t)archive_le32dec(extdheader);
				lha->gid = archive_le32dec(extdheader+4);
				lha->uid = archive_le32dec(extdheader+8);
				lha->birthtime = archive_le32dec(extdheader+12);
				lha->atime = archive_le32dec(extdheader+16);
				lha->setflag |= UNIX_MODE_IS_SET
				    | BIRTHTIME_IS_SET | ATIME_IS_SET;
			}
			break;
		case EXT_TIMEZONE:		/* Not supported */
		case EXT_UTF16_FILENAME:	/* Not supported */
		case EXT_UTF16_DIRECTORY:	/* Not supported */
		default:
			break;
		}

		__archive_read_consume(a, extdsize);
	}
invalid:
	archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
	    "Invalid extended LHa header");
	return (ARCHIVE_FATAL);
}