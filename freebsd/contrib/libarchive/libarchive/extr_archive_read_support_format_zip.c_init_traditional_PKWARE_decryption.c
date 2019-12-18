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
typedef  scalar_t__ uint8_t ;
struct zip {int tctx_valid; scalar_t__ entry_bytes_remaining; scalar_t__ decrypted_bytes_remaining; int /*<<< orphan*/  entry_compressed_bytes_read; TYPE_2__* entry; int /*<<< orphan*/  tctx; } ;
struct archive_read {int /*<<< orphan*/  archive; TYPE_1__* format; } ;
typedef  int /*<<< orphan*/  intmax_t ;
struct TYPE_4__ {int zip_flags; scalar_t__ decdat; } ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 scalar_t__ ENC_HEADER_SIZE ; 
 int ZIP_LENGTH_AT_END ; 
 void* __archive_read_ahead (struct archive_read*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __archive_read_consume (struct archive_read*,scalar_t__) ; 
 char* __archive_read_next_passphrase (struct archive_read*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int trad_enc_init (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,void const*,scalar_t__,scalar_t__*) ; 
 int zip_alloc_decryption_buffer (struct archive_read*) ; 

__attribute__((used)) static int
init_traditional_PKWARE_decryption(struct archive_read *a)
{
	struct zip *zip = (struct zip *)(a->format->data);
	const void *p;
	int retry;
	int r;

	if (zip->tctx_valid)
		return (ARCHIVE_OK);

	/*
	   Read the 12 bytes encryption header stored at
	   the start of the data area.
	 */
#define ENC_HEADER_SIZE	12
	if (0 == (zip->entry->zip_flags & ZIP_LENGTH_AT_END)
	    && zip->entry_bytes_remaining < ENC_HEADER_SIZE) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Truncated Zip encrypted body: only %jd bytes available",
		    (intmax_t)zip->entry_bytes_remaining);
		return (ARCHIVE_FATAL);
	}

	p = __archive_read_ahead(a, ENC_HEADER_SIZE, NULL);
	if (p == NULL) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Truncated ZIP file data");
		return (ARCHIVE_FATAL);
	}

	for (retry = 0;; retry++) {
		const char *passphrase;
		uint8_t crcchk;

		passphrase = __archive_read_next_passphrase(a);
		if (passphrase == NULL) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    (retry > 0)?
				"Incorrect passphrase":
				"Passphrase required for this entry");
			return (ARCHIVE_FAILED);
		}

		/*
		 * Initialize ctx for Traditional PKWARE Decryption.
		 */
		r = trad_enc_init(&zip->tctx, passphrase, strlen(passphrase),
			p, ENC_HEADER_SIZE, &crcchk);
		if (r == 0 && crcchk == zip->entry->decdat)
			break;/* The passphrase is OK. */
		if (retry > 10000) {
			/* Avoid infinity loop. */
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Too many incorrect passphrases");
			return (ARCHIVE_FAILED);
		}
	}

	__archive_read_consume(a, ENC_HEADER_SIZE);
	zip->tctx_valid = 1;
	if (0 == (zip->entry->zip_flags & ZIP_LENGTH_AT_END)) {
	    zip->entry_bytes_remaining -= ENC_HEADER_SIZE;
	}
	/*zip->entry_uncompressed_bytes_read += ENC_HEADER_SIZE;*/
	zip->entry_compressed_bytes_read += ENC_HEADER_SIZE;
	zip->decrypted_bytes_remaining = 0;

	return (zip_alloc_decryption_buffer(a));
#undef ENC_HEADER_SIZE
}