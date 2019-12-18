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
struct rar {scalar_t__ has_encrypted_entries; scalar_t__ bytes_unconsumed; scalar_t__ offset_seek; scalar_t__ unp_size; scalar_t__ offset; int compression_method; int start_new_table; int /*<<< orphan*/  ppmd_valid; int /*<<< orphan*/  ppmd7_context; scalar_t__ entry_eof; } ;
struct archive_read {int /*<<< orphan*/  archive; TYPE_1__* format; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* Ppmd7_Free ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 scalar_t__ ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW ; 
 int ARCHIVE_WARN ; 
#define  COMPRESS_METHOD_BEST 133 
#define  COMPRESS_METHOD_FAST 132 
#define  COMPRESS_METHOD_FASTEST 131 
#define  COMPRESS_METHOD_GOOD 130 
#define  COMPRESS_METHOD_NORMAL 129 
#define  COMPRESS_METHOD_STORE 128 
 TYPE_2__ __archive_ppmd7_functions ; 
 int /*<<< orphan*/  __archive_read_consume (struct archive_read*,scalar_t__) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int read_data_compressed (struct archive_read*,void const**,size_t*,scalar_t__*) ; 
 int read_data_stored (struct archive_read*,void const**,size_t*,scalar_t__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
archive_read_format_rar_read_data(struct archive_read *a, const void **buff,
                                  size_t *size, int64_t *offset)
{
  struct rar *rar = (struct rar *)(a->format->data);
  int ret;

  if (rar->has_encrypted_entries == ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW) {
	  rar->has_encrypted_entries = 0;
  }

  if (rar->bytes_unconsumed > 0) {
      /* Consume as much as the decompressor actually used. */
      __archive_read_consume(a, rar->bytes_unconsumed);
      rar->bytes_unconsumed = 0;
  }

  *buff = NULL;
  if (rar->entry_eof || rar->offset_seek >= rar->unp_size) {
    *size = 0;
    *offset = rar->offset;
    if (*offset < rar->unp_size)
      *offset = rar->unp_size;
    return (ARCHIVE_EOF);
  }

  switch (rar->compression_method)
  {
  case COMPRESS_METHOD_STORE:
    ret = read_data_stored(a, buff, size, offset);
    break;

  case COMPRESS_METHOD_FASTEST:
  case COMPRESS_METHOD_FAST:
  case COMPRESS_METHOD_NORMAL:
  case COMPRESS_METHOD_GOOD:
  case COMPRESS_METHOD_BEST:
    ret = read_data_compressed(a, buff, size, offset);
    if (ret != ARCHIVE_OK && ret != ARCHIVE_WARN) {
      __archive_ppmd7_functions.Ppmd7_Free(&rar->ppmd7_context);
      rar->start_new_table = 1;
      rar->ppmd_valid = 0;
    }
    break;

  default:
    archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                      "Unsupported compression method for RAR file.");
    ret = ARCHIVE_FATAL;
    break;
  }
  return (ret);
}