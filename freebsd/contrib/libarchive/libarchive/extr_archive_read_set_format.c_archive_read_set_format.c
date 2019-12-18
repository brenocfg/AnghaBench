#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct archive_read {int /*<<< orphan*/  archive; TYPE_1__* format; TYPE_1__* formats; } ;
struct archive {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_PROGRAMMER ; 
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
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 int archive_read_support_format_by_code (struct archive*,int) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int
archive_read_set_format(struct archive *_a, int code)
{
  int r1, r2, slots, i;
  char str[10];
  struct archive_read *a = (struct archive_read *)_a;

  if ((r1 = archive_read_support_format_by_code(_a, code)) < (ARCHIVE_OK))
    return r1;

  r1 = r2 = (ARCHIVE_OK);
  if (a->format)
    r2 = (ARCHIVE_WARN);
  switch (code & ARCHIVE_FORMAT_BASE_MASK)
  {
    case ARCHIVE_FORMAT_7ZIP:
      strcpy(str, "7zip");
      break;
    case ARCHIVE_FORMAT_AR:
      strcpy(str, "ar");
      break;
    case ARCHIVE_FORMAT_CAB:
      strcpy(str, "cab");
      break;
    case ARCHIVE_FORMAT_CPIO:
      strcpy(str, "cpio");
      break;
    case ARCHIVE_FORMAT_ISO9660:
      strcpy(str, "iso9660");
      break;
    case ARCHIVE_FORMAT_LHA:
      strcpy(str, "lha");
      break;
    case ARCHIVE_FORMAT_MTREE:
      strcpy(str, "mtree");
      break;
    case ARCHIVE_FORMAT_RAR:
      strcpy(str, "rar");
      break;
    case ARCHIVE_FORMAT_RAR_V5:
      strcpy(str, "rar5");
      break;
    case ARCHIVE_FORMAT_TAR:
      strcpy(str, "tar");
      break;
    case ARCHIVE_FORMAT_XAR:
      strcpy(str, "xar");
      break;
    case ARCHIVE_FORMAT_ZIP:
      strcpy(str, "zip");
      break;
    default:
      archive_set_error(&a->archive, ARCHIVE_ERRNO_PROGRAMMER,
          "Invalid format code specified");
      return (ARCHIVE_FATAL);
  }

  slots = sizeof(a->formats) / sizeof(a->formats[0]);
  a->format = &(a->formats[0]);
  for (i = 0; i < slots; i++, a->format++) {
    if (!a->format->name || !strcmp(a->format->name, str))
      break;
  }
  if (!a->format->name || strcmp(a->format->name, str))
  {
    archive_set_error(&a->archive, ARCHIVE_ERRNO_PROGRAMMER,
        "Internal error: Unable to set format");
    r1 = (ARCHIVE_FATAL);
  }

  return (r1 < r2) ? r1 : r2;
}