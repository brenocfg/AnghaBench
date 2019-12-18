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
struct rar {scalar_t__ compression_method; scalar_t__ offset_seek; scalar_t__ unp_size; unsigned int cursor; int main_flags; int file_flags; size_t nodes; int has_endarc_header; scalar_t__ offset; scalar_t__ bytes_unconsumed; TYPE_2__* dbo; scalar_t__ bytes_remaining; } ;
struct archive_read {int /*<<< orphan*/  archive; int /*<<< orphan*/  entry; TYPE_1__* format; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {scalar_t__ start_offset; scalar_t__ end_offset; scalar_t__ header_size; } ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ ARCHIVE_EOF ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 scalar_t__ ARCHIVE_FAILED ; 
 scalar_t__ ARCHIVE_OK ; 
 scalar_t__ COMPRESS_METHOD_STORE ; 
 int FHD_SPLIT_AFTER ; 
 int FHD_SPLIT_BEFORE ; 
 int MHD_VOLUME ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 scalar_t__ __archive_read_seek (struct archive_read*,scalar_t__,int const) ; 
 int /*<<< orphan*/  __archive_reset_read_data (int /*<<< orphan*/ *) ; 
 scalar_t__ archive_read_format_rar_read_header (struct archive_read*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int64_t
archive_read_format_rar_seek_data(struct archive_read *a, int64_t offset,
    int whence)
{
  int64_t client_offset, ret;
  unsigned int i;
  struct rar *rar = (struct rar *)(a->format->data);

  if (rar->compression_method == COMPRESS_METHOD_STORE)
  {
    /* Modify the offset for use with SEEK_SET */
    switch (whence)
    {
      case SEEK_CUR:
        client_offset = rar->offset_seek;
        break;
      case SEEK_END:
        client_offset = rar->unp_size;
        break;
      case SEEK_SET:
      default:
        client_offset = 0;
    }
    client_offset += offset;
    if (client_offset < 0)
    {
      /* Can't seek past beginning of data block */
      return -1;
    }
    else if (client_offset > rar->unp_size)
    {
      /*
       * Set the returned offset but only seek to the end of
       * the data block.
       */
      rar->offset_seek = client_offset;
      client_offset = rar->unp_size;
    }

    client_offset += rar->dbo[0].start_offset;
    i = 0;
    while (i < rar->cursor)
    {
      i++;
      client_offset += rar->dbo[i].start_offset - rar->dbo[i-1].end_offset;
    }
    if (rar->main_flags & MHD_VOLUME)
    {
      /* Find the appropriate offset among the multivolume archive */
      while (1)
      {
        if (client_offset < rar->dbo[rar->cursor].start_offset &&
          rar->file_flags & FHD_SPLIT_BEFORE)
        {
          /* Search backwards for the correct data block */
          if (rar->cursor == 0)
          {
            archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
              "Attempt to seek past beginning of RAR data block");
            return (ARCHIVE_FAILED);
          }
          rar->cursor--;
          client_offset -= rar->dbo[rar->cursor+1].start_offset -
            rar->dbo[rar->cursor].end_offset;
          if (client_offset < rar->dbo[rar->cursor].start_offset)
            continue;
          ret = __archive_read_seek(a, rar->dbo[rar->cursor].start_offset -
            rar->dbo[rar->cursor].header_size, SEEK_SET);
          if (ret < (ARCHIVE_OK))
            return ret;
          ret = archive_read_format_rar_read_header(a, a->entry);
          if (ret != (ARCHIVE_OK))
          {
            archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
              "Error during seek of RAR file");
            return (ARCHIVE_FAILED);
          }
          rar->cursor--;
          break;
        }
        else if (client_offset > rar->dbo[rar->cursor].end_offset &&
          rar->file_flags & FHD_SPLIT_AFTER)
        {
          /* Search forward for the correct data block */
          rar->cursor++;
          if (rar->cursor < rar->nodes &&
            client_offset > rar->dbo[rar->cursor].end_offset)
          {
            client_offset += rar->dbo[rar->cursor].start_offset -
              rar->dbo[rar->cursor-1].end_offset;
            continue;
          }
          rar->cursor--;
          ret = __archive_read_seek(a, rar->dbo[rar->cursor].end_offset,
                                    SEEK_SET);
          if (ret < (ARCHIVE_OK))
            return ret;
          ret = archive_read_format_rar_read_header(a, a->entry);
          if (ret == (ARCHIVE_EOF))
          {
            rar->has_endarc_header = 1;
            ret = archive_read_format_rar_read_header(a, a->entry);
          }
          if (ret != (ARCHIVE_OK))
          {
            archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
              "Error during seek of RAR file");
            return (ARCHIVE_FAILED);
          }
          client_offset += rar->dbo[rar->cursor].start_offset -
            rar->dbo[rar->cursor-1].end_offset;
          continue;
        }
        break;
      }
    }

    ret = __archive_read_seek(a, client_offset, SEEK_SET);
    if (ret < (ARCHIVE_OK))
      return ret;
    rar->bytes_remaining = rar->dbo[rar->cursor].end_offset - ret;
    i = rar->cursor;
    while (i > 0)
    {
      i--;
      ret -= rar->dbo[i+1].start_offset - rar->dbo[i].end_offset;
    }
    ret -= rar->dbo[0].start_offset;

    /* Always restart reading the file after a seek */
    __archive_reset_read_data(&a->archive);

    rar->bytes_unconsumed = 0;
    rar->offset = 0;

    /*
     * If a seek past the end of file was requested, return the requested
     * offset.
     */
    if (ret == rar->unp_size && rar->offset_seek > rar->unp_size)
      return rar->offset_seek;

    /* Return the new offset */
    rar->offset_seek = ret;
    return rar->offset_seek;
  }
  else
  {
    archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
      "Seeking of compressed RAR files is unsupported");
  }
  return (ARCHIVE_FAILED);
}