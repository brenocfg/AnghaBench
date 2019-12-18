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
struct zip_entry {int dummy; } ;
struct zip {scalar_t__ has_encrypted_entries; scalar_t__ unconsumed; scalar_t__ hctx_valid; scalar_t__ cctx_valid; scalar_t__ tctx_valid; int /*<<< orphan*/  hctx; int /*<<< orphan*/  cctx; int /*<<< orphan*/ * entry; int /*<<< orphan*/ * zip_entries; } ;
struct TYPE_4__ {char* archive_format_name; int /*<<< orphan*/  archive_format; } ;
struct archive_read {TYPE_2__ archive; TYPE_1__* format; } ;
struct archive_entry {int dummy; } ;
typedef  int ssize_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_ZIP ; 
 scalar_t__ ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW ; 
 int /*<<< orphan*/  ENOMEM ; 
 char* __archive_read_ahead (struct archive_read*,int,int*) ; 
 int /*<<< orphan*/  __archive_read_consume (struct archive_read*,scalar_t__) ; 
 int /*<<< orphan*/  __archive_read_reset_passphrase (struct archive_read*) ; 
 int /*<<< orphan*/  archive_decrypto_aes_ctr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_hmac_sha1_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_set_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int zip_read_local_file_header (struct archive_read*,struct archive_entry*,struct zip*) ; 

__attribute__((used)) static int
archive_read_format_zip_streamable_read_header(struct archive_read *a,
    struct archive_entry *entry)
{
	struct zip *zip;

	a->archive.archive_format = ARCHIVE_FORMAT_ZIP;
	if (a->archive.archive_format_name == NULL)
		a->archive.archive_format_name = "ZIP";

	zip = (struct zip *)(a->format->data);

	/*
	 * It should be sufficient to call archive_read_next_header() for
	 * a reader to determine if an entry is encrypted or not. If the
	 * encryption of an entry is only detectable when calling
	 * archive_read_data(), so be it. We'll do the same check there
	 * as well.
	 */
	if (zip->has_encrypted_entries ==
			ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW)
		zip->has_encrypted_entries = 0;

	/* Make sure we have a zip_entry structure to use. */
	if (zip->zip_entries == NULL) {
		zip->zip_entries = malloc(sizeof(struct zip_entry));
		if (zip->zip_entries == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "Out  of memory");
			return ARCHIVE_FATAL;
		}
	}
	zip->entry = zip->zip_entries;
	memset(zip->entry, 0, sizeof(struct zip_entry));

	if (zip->cctx_valid)
		archive_decrypto_aes_ctr_release(&zip->cctx);
	if (zip->hctx_valid)
		archive_hmac_sha1_cleanup(&zip->hctx);
	zip->tctx_valid = zip->cctx_valid = zip->hctx_valid = 0;
	__archive_read_reset_passphrase(a);

	/* Search ahead for the next local file header. */
	__archive_read_consume(a, zip->unconsumed);
	zip->unconsumed = 0;
	for (;;) {
		int64_t skipped = 0;
		const char *p, *end;
		ssize_t bytes;

		p = __archive_read_ahead(a, 4, &bytes);
		if (p == NULL)
			return (ARCHIVE_FATAL);
		end = p + bytes;

		while (p + 4 <= end) {
			if (p[0] == 'P' && p[1] == 'K') {
				if (p[2] == '\003' && p[3] == '\004') {
					/* Regular file entry. */
					__archive_read_consume(a, skipped);
					return zip_read_local_file_header(a,
					    entry, zip);
				}

                              /*
                               * TODO: We cannot restore permissions
                               * based only on the local file headers.
                               * Consider scanning the central
                               * directory and returning additional
                               * entries for at least directories.
                               * This would allow us to properly set
                               * directory permissions.
			       *
			       * This won't help us fix symlinks
			       * and may not help with regular file
			       * permissions, either.  <sigh>
                               */
                              if (p[2] == '\001' && p[3] == '\002') {
                                      return (ARCHIVE_EOF);
                              }

                              /* End of central directory?  Must be an
                               * empty archive. */
                              if ((p[2] == '\005' && p[3] == '\006')
                                  || (p[2] == '\006' && p[3] == '\006'))
                                      return (ARCHIVE_EOF);
			}
			++p;
			++skipped;
		}
		__archive_read_consume(a, skipped);
	}
}