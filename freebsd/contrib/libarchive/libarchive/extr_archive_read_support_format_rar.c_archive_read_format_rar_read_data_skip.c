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
struct rar {scalar_t__ bytes_unconsumed; scalar_t__ bytes_remaining; int main_flags; int file_flags; } ;
struct archive_read {int /*<<< orphan*/  entry; TYPE_1__* format; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int FHD_SPLIT_AFTER ; 
 int MHD_VOLUME ; 
 scalar_t__ __archive_read_consume (struct archive_read*,scalar_t__) ; 
 int archive_read_format_rar_read_header (struct archive_read*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
archive_read_format_rar_read_data_skip(struct archive_read *a)
{
  struct rar *rar;
  int64_t bytes_skipped;
  int ret;

  rar = (struct rar *)(a->format->data);

  if (rar->bytes_unconsumed > 0) {
      /* Consume as much as the decompressor actually used. */
      __archive_read_consume(a, rar->bytes_unconsumed);
      rar->bytes_unconsumed = 0;
  }

  if (rar->bytes_remaining > 0) {
    bytes_skipped = __archive_read_consume(a, rar->bytes_remaining);
    if (bytes_skipped < 0)
      return (ARCHIVE_FATAL);
  }

  /* Compressed data to skip must be read from each header in a multivolume
   * archive.
   */
  if (rar->main_flags & MHD_VOLUME && rar->file_flags & FHD_SPLIT_AFTER)
  {
    ret = archive_read_format_rar_read_header(a, a->entry);
    if (ret == (ARCHIVE_EOF))
      ret = archive_read_format_rar_read_header(a, a->entry);
    if (ret != (ARCHIVE_OK))
      return ret;
    return archive_read_format_rar_read_data_skip(a);
  }

  return (ARCHIVE_OK);
}