#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rar {scalar_t__ bytes_remaining; int main_flags; int file_flags; int filename_must_match; int has_endarc_header; } ;
struct TYPE_4__ {scalar_t__ read_data_requested; scalar_t__ read_data_is_posix_read; } ;
struct archive_read {int /*<<< orphan*/  entry; TYPE_2__ archive; TYPE_1__* format; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int ARCHIVE_OK ; 
 int FHD_SPLIT_AFTER ; 
 int MHD_VOLUME ; 
 void* __archive_read_ahead (struct archive_read*,size_t,scalar_t__*) ; 
 int archive_read_format_rar_read_header (struct archive_read*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const void *
rar_read_ahead(struct archive_read *a, size_t min, ssize_t *avail)
{
  struct rar *rar = (struct rar *)(a->format->data);
  const void *h = __archive_read_ahead(a, min, avail);
  int ret;
  if (avail)
  {
    if (a->archive.read_data_is_posix_read && *avail > (ssize_t)a->archive.read_data_requested)
      *avail = a->archive.read_data_requested;
    if (*avail > rar->bytes_remaining)
      *avail = (ssize_t)rar->bytes_remaining;
    if (*avail < 0)
      return NULL;
    else if (*avail == 0 && rar->main_flags & MHD_VOLUME &&
      rar->file_flags & FHD_SPLIT_AFTER)
    {
      rar->filename_must_match = 1;
      ret = archive_read_format_rar_read_header(a, a->entry);
      if (ret == (ARCHIVE_EOF))
      {
        rar->has_endarc_header = 1;
        ret = archive_read_format_rar_read_header(a, a->entry);
      }
      rar->filename_must_match = 0;
      if (ret != (ARCHIVE_OK))
        return NULL;
      return rar_read_ahead(a, min, avail);
    }
  }
  return h;
}