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
struct archive_entry_linkresolver {void* strategy; } ;

/* Variables and functions */
 void* ARCHIVE_ENTRY_LINKIFY_LIKE_MTREE ; 
 void* ARCHIVE_ENTRY_LINKIFY_LIKE_NEW_CPIO ; 
 void* ARCHIVE_ENTRY_LINKIFY_LIKE_OLD_CPIO ; 
 void* ARCHIVE_ENTRY_LINKIFY_LIKE_TAR ; 
#define  ARCHIVE_FORMAT_7ZIP 138 
#define  ARCHIVE_FORMAT_AR 137 
 int ARCHIVE_FORMAT_BASE_MASK ; 
#define  ARCHIVE_FORMAT_CPIO 136 
#define  ARCHIVE_FORMAT_CPIO_SVR4_CRC 135 
#define  ARCHIVE_FORMAT_CPIO_SVR4_NOCRC 134 
#define  ARCHIVE_FORMAT_ISO9660 133 
#define  ARCHIVE_FORMAT_MTREE 132 
#define  ARCHIVE_FORMAT_SHAR 131 
#define  ARCHIVE_FORMAT_TAR 130 
#define  ARCHIVE_FORMAT_XAR 129 
#define  ARCHIVE_FORMAT_ZIP 128 

void
archive_entry_linkresolver_set_strategy(struct archive_entry_linkresolver *res,
    int fmt)
{
	int fmtbase = fmt & ARCHIVE_FORMAT_BASE_MASK;

	switch (fmtbase) {
	case ARCHIVE_FORMAT_7ZIP:
	case ARCHIVE_FORMAT_AR:
	case ARCHIVE_FORMAT_ZIP:
		res->strategy = ARCHIVE_ENTRY_LINKIFY_LIKE_OLD_CPIO;
		break;
	case ARCHIVE_FORMAT_CPIO:
		switch (fmt) {
		case ARCHIVE_FORMAT_CPIO_SVR4_NOCRC:
		case ARCHIVE_FORMAT_CPIO_SVR4_CRC:
			res->strategy = ARCHIVE_ENTRY_LINKIFY_LIKE_NEW_CPIO;
			break;
		default:
			res->strategy = ARCHIVE_ENTRY_LINKIFY_LIKE_OLD_CPIO;
			break;
		}
		break;
	case ARCHIVE_FORMAT_MTREE:
		res->strategy = ARCHIVE_ENTRY_LINKIFY_LIKE_MTREE;
		break;
	case ARCHIVE_FORMAT_ISO9660:
	case ARCHIVE_FORMAT_SHAR:
	case ARCHIVE_FORMAT_TAR:
	case ARCHIVE_FORMAT_XAR:
		res->strategy = ARCHIVE_ENTRY_LINKIFY_LIKE_TAR;
		break;
	default:
		res->strategy = ARCHIVE_ENTRY_LINKIFY_LIKE_OLD_CPIO;
		break;
	}
}