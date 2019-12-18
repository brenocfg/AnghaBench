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
struct rar {scalar_t__ has_encrypted_entries; int found_first_header; unsigned long main_flags; char encryptver; int /*<<< orphan*/  reserved2; int /*<<< orphan*/  reserved1; } ;
struct TYPE_4__ {char* archive_format_name; int /*<<< orphan*/  archive_format; } ;
struct archive_read {TYPE_2__ archive; TYPE_1__* format; } ;
struct archive_entry {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_RAR ; 
 scalar_t__ ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW ; 
 int ARCHIVE_WARN ; 
#define  AV_HEAD 137 
#define  COMM_HEAD 136 
#define  ENDARC_HEAD 135 
#define  FILE_HEAD 134 
 unsigned int HD_ADD_SIZE_PRESENT ; 
#define  MAIN_HEAD 133 
#define  MARK_HEAD 132 
 int MHD_ENCRYPTVER ; 
 int MHD_PASSWORD ; 
#define  NEWSUB_HEAD 131 
#define  PROTECT_HEAD 130 
 char* RAR_SIGNATURE ; 
#define  SIGN_HEAD 129 
#define  SUB_HEAD 128 
 void* __archive_read_ahead (struct archive_read*,size_t,size_t*) ; 
 int /*<<< orphan*/  __archive_read_consume (struct archive_read*,size_t) ; 
 int /*<<< orphan*/  archive_entry_set_is_data_encrypted (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_entry_set_is_metadata_encrypted (struct archive_entry*,int) ; 
 unsigned long archive_le16dec (char const*) ; 
 size_t archive_le32dec (char const*) ; 
 int /*<<< orphan*/  archive_set_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 unsigned long crc32 (unsigned long,unsigned char const*,unsigned int) ; 
 scalar_t__ memcmp (char const*,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int read_header (struct archive_read*,struct archive_entry*,char) ; 
 int skip_sfx (struct archive_read*) ; 

__attribute__((used)) static int
archive_read_format_rar_read_header(struct archive_read *a,
                                    struct archive_entry *entry)
{
  const void *h;
  const char *p;
  struct rar *rar;
  size_t skip;
  char head_type;
  int ret;
  unsigned flags;
  unsigned long crc32_expected;

  a->archive.archive_format = ARCHIVE_FORMAT_RAR;
  if (a->archive.archive_format_name == NULL)
    a->archive.archive_format_name = "RAR";

  rar = (struct rar *)(a->format->data);

  /*
   * It should be sufficient to call archive_read_next_header() for
   * a reader to determine if an entry is encrypted or not. If the
   * encryption of an entry is only detectable when calling
   * archive_read_data(), so be it. We'll do the same check there
   * as well.
   */
  if (rar->has_encrypted_entries == ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW) {
	  rar->has_encrypted_entries = 0;
  }

  /* RAR files can be generated without EOF headers, so return ARCHIVE_EOF if
  * this fails.
  */
  if ((h = __archive_read_ahead(a, 7, NULL)) == NULL)
    return (ARCHIVE_EOF);

  p = h;
  if (rar->found_first_header == 0 &&
     ((p[0] == 'M' && p[1] == 'Z') || memcmp(p, "\x7F\x45LF", 4) == 0)) {
    /* This is an executable ? Must be self-extracting... */
    ret = skip_sfx(a);
    if (ret < ARCHIVE_WARN)
      return (ret);
  }
  rar->found_first_header = 1;

  while (1)
  {
    unsigned long crc32_val;

    if ((h = __archive_read_ahead(a, 7, NULL)) == NULL)
      return (ARCHIVE_FATAL);
    p = h;

    head_type = p[2];
    switch(head_type)
    {
    case MARK_HEAD:
      if (memcmp(p, RAR_SIGNATURE, 7) != 0) {
        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
          "Invalid marker header");
        return (ARCHIVE_FATAL);
      }
      __archive_read_consume(a, 7);
      break;

    case MAIN_HEAD:
      rar->main_flags = archive_le16dec(p + 3);
      skip = archive_le16dec(p + 5);
      if (skip < 7 + sizeof(rar->reserved1) + sizeof(rar->reserved2)) {
        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
          "Invalid header size");
        return (ARCHIVE_FATAL);
      }
      if ((h = __archive_read_ahead(a, skip, NULL)) == NULL)
        return (ARCHIVE_FATAL);
      p = h;
      memcpy(rar->reserved1, p + 7, sizeof(rar->reserved1));
      memcpy(rar->reserved2, p + 7 + sizeof(rar->reserved1),
             sizeof(rar->reserved2));
      if (rar->main_flags & MHD_ENCRYPTVER) {
        if (skip < 7 + sizeof(rar->reserved1) + sizeof(rar->reserved2)+1) {
          archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
            "Invalid header size");
          return (ARCHIVE_FATAL);
        }
        rar->encryptver = *(p + 7 + sizeof(rar->reserved1) +
                            sizeof(rar->reserved2));
      }

      /* Main header is password encrypted, so we cannot read any
         file names or any other info about files from the header. */
      if (rar->main_flags & MHD_PASSWORD)
      {
        archive_entry_set_is_metadata_encrypted(entry, 1);
        archive_entry_set_is_data_encrypted(entry, 1);
        rar->has_encrypted_entries = 1;
         archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                          "RAR encryption support unavailable.");
        return (ARCHIVE_FATAL);
      }

      crc32_val = crc32(0, (const unsigned char *)p + 2, (unsigned)skip - 2);
      if ((crc32_val & 0xffff) != archive_le16dec(p)) {
        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
          "Header CRC error");
        return (ARCHIVE_FATAL);
      }
      __archive_read_consume(a, skip);
      break;

    case FILE_HEAD:
      return read_header(a, entry, head_type);

    case COMM_HEAD:
    case AV_HEAD:
    case SUB_HEAD:
    case PROTECT_HEAD:
    case SIGN_HEAD:
    case ENDARC_HEAD:
      flags = archive_le16dec(p + 3);
      skip = archive_le16dec(p + 5);
      if (skip < 7) {
        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
          "Invalid header size too small");
        return (ARCHIVE_FATAL);
      }
      if (flags & HD_ADD_SIZE_PRESENT)
      {
        if (skip < 7 + 4) {
          archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
            "Invalid header size too small");
          return (ARCHIVE_FATAL);
        }
        if ((h = __archive_read_ahead(a, skip, NULL)) == NULL)
          return (ARCHIVE_FATAL);
        p = h;
        skip += archive_le32dec(p + 7);
      }

      /* Skip over the 2-byte CRC at the beginning of the header. */
      crc32_expected = archive_le16dec(p);
      __archive_read_consume(a, 2);
      skip -= 2;

      /* Skim the entire header and compute the CRC. */
      crc32_val = 0;
      while (skip > 0) {
	      size_t to_read = skip;
	      ssize_t did_read;
	      if (to_read > 32 * 1024) {
		      to_read = 32 * 1024;
	      }
	      if ((h = __archive_read_ahead(a, to_read, &did_read)) == NULL) {
		      return (ARCHIVE_FATAL);
	      }
	      p = h;
	      crc32_val = crc32(crc32_val, (const unsigned char *)p, (unsigned)did_read);
	      __archive_read_consume(a, did_read);
	      skip -= did_read;
      }
      if ((crc32_val & 0xffff) != crc32_expected) {
	      archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		  "Header CRC error");
	      return (ARCHIVE_FATAL);
      }
      if (head_type == ENDARC_HEAD)
	      return (ARCHIVE_EOF);
      break;

    case NEWSUB_HEAD:
      if ((ret = read_header(a, entry, head_type)) < ARCHIVE_WARN)
        return ret;
      break;

    default:
      archive_set_error(&a->archive,  ARCHIVE_ERRNO_FILE_FORMAT,
                        "Bad RAR file");
      return (ARCHIVE_FATAL);
    }
  }
}