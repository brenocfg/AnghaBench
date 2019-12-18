#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * window; } ;
struct rar {void* unp_buffer; int unp_buffer_size; size_t unp_offset; TYPE_2__ lzss; } ;
struct archive_read {int /*<<< orphan*/  archive; TYPE_1__* format; } ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_4__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int lzss_offset_for_position (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int lzss_size (TYPE_2__*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
copy_from_lzss_window(struct archive_read *a, const void **buffer,
                        int64_t startpos, int length)
{
  int windowoffs, firstpart;
  struct rar *rar = (struct rar *)(a->format->data);

  if (!rar->unp_buffer)
  {
    if ((rar->unp_buffer = malloc(rar->unp_buffer_size)) == NULL)
    {
      archive_set_error(&a->archive, ENOMEM,
                        "Unable to allocate memory for uncompressed data.");
      return (ARCHIVE_FATAL);
    }
  }

  windowoffs = lzss_offset_for_position(&rar->lzss, startpos);
  if(windowoffs + length <= lzss_size(&rar->lzss)) {
    memcpy(&rar->unp_buffer[rar->unp_offset], &rar->lzss.window[windowoffs],
           length);
  } else if (length <= lzss_size(&rar->lzss)) {
    firstpart = lzss_size(&rar->lzss) - windowoffs;
    if (firstpart < 0) {
      archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                        "Bad RAR file data");
      return (ARCHIVE_FATAL);
    }
    if (firstpart < length) {
      memcpy(&rar->unp_buffer[rar->unp_offset],
             &rar->lzss.window[windowoffs], firstpart);
      memcpy(&rar->unp_buffer[rar->unp_offset + firstpart],
             &rar->lzss.window[0], length - firstpart);
    } else {
      memcpy(&rar->unp_buffer[rar->unp_offset],
             &rar->lzss.window[windowoffs], length);
    }
  } else {
      archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                        "Bad RAR file data");
      return (ARCHIVE_FATAL);
  }
  rar->unp_offset += length;
  if (rar->unp_offset >= rar->unp_buffer_size)
    *buffer = rar->unp_buffer;
  else
    *buffer = NULL;
  return (ARCHIVE_OK);
}