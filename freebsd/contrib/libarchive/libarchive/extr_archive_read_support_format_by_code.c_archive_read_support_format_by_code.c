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
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
#define  ARCHIVE_FORMAT_7ZIP 139 
#define  ARCHIVE_FORMAT_AR 138 
 int ARCHIVE_FORMAT_BASE_MASK ; 
#define  ARCHIVE_FORMAT_CAB 137 
#define  ARCHIVE_FORMAT_CPIO 136 
#define  ARCHIVE_FORMAT_ISO9660 135 
#define  ARCHIVE_FORMAT_LHA 134 
#define  ARCHIVE_FORMAT_MTREE 133 
#define  ARCHIVE_FORMAT_RAR 132 
#define  ARCHIVE_FORMAT_RAR_V5 131 
#define  ARCHIVE_FORMAT_TAR 130 
#define  ARCHIVE_FORMAT_XAR 129 
#define  ARCHIVE_FORMAT_ZIP 128 
 int /*<<< orphan*/  ARCHIVE_READ_MAGIC ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int archive_read_support_format_7zip (struct archive*) ; 
 int archive_read_support_format_ar (struct archive*) ; 
 int archive_read_support_format_cab (struct archive*) ; 
 int archive_read_support_format_cpio (struct archive*) ; 
 int archive_read_support_format_iso9660 (struct archive*) ; 
 int archive_read_support_format_lha (struct archive*) ; 
 int archive_read_support_format_mtree (struct archive*) ; 
 int archive_read_support_format_rar (struct archive*) ; 
 int archive_read_support_format_rar5 (struct archive*) ; 
 int archive_read_support_format_tar (struct archive*) ; 
 int archive_read_support_format_xar (struct archive*) ; 
 int archive_read_support_format_zip (struct archive*) ; 

int
archive_read_support_format_by_code(struct archive *a, int format_code)
{
	archive_check_magic(a, ARCHIVE_READ_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_read_support_format_by_code");

	switch (format_code & ARCHIVE_FORMAT_BASE_MASK) {
	case ARCHIVE_FORMAT_7ZIP:
		return archive_read_support_format_7zip(a);
		break;
	case ARCHIVE_FORMAT_AR:
		return archive_read_support_format_ar(a);
		break;
	case ARCHIVE_FORMAT_CAB:
		return archive_read_support_format_cab(a);
		break;
	case ARCHIVE_FORMAT_CPIO:
		return archive_read_support_format_cpio(a);
		break;
	case ARCHIVE_FORMAT_ISO9660:
		return archive_read_support_format_iso9660(a);
		break;
	case ARCHIVE_FORMAT_LHA:
		return archive_read_support_format_lha(a);
		break;
	case ARCHIVE_FORMAT_MTREE:
		return archive_read_support_format_mtree(a);
		break;
	case ARCHIVE_FORMAT_RAR:
		return archive_read_support_format_rar(a);
		break;
	case ARCHIVE_FORMAT_RAR_V5:
		return archive_read_support_format_rar5(a);
		break;
	case ARCHIVE_FORMAT_TAR:
		return archive_read_support_format_tar(a);
		break;
	case ARCHIVE_FORMAT_XAR:
		return archive_read_support_format_xar(a);
		break;
	case ARCHIVE_FORMAT_ZIP:
		return archive_read_support_format_zip(a);
		break;
	}
	return (ARCHIVE_FATAL);
}