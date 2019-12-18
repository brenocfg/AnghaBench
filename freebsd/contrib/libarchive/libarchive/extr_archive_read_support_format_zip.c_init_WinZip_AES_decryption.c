#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ const uint8_t ;
struct zip {int cctx_valid; int hctx_valid; scalar_t__ entry_bytes_remaining; TYPE_3__* entry; scalar_t__ decrypted_bytes_remaining; int /*<<< orphan*/  entry_compressed_bytes_read; int /*<<< orphan*/  cctx; int /*<<< orphan*/  hctx; } ;
struct archive_read {int /*<<< orphan*/  archive; TYPE_1__* format; } ;
typedef  int /*<<< orphan*/  derived_key ;
struct TYPE_5__ {int strength; int /*<<< orphan*/  compression; } ;
struct TYPE_6__ {int zip_flags; TYPE_2__ aes_extra; int /*<<< orphan*/  compression; } ;
struct TYPE_4__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 scalar_t__ AUTH_CODE_SIZE ; 
 int MAX_DERIVED_KEY_BUF_SIZE ; 
 int ZIP_LENGTH_AT_END ; 
 void* __archive_read_ahead (struct archive_read*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __archive_read_consume (struct archive_read*,size_t) ; 
 char* __archive_read_next_passphrase (struct archive_read*) ; 
 int archive_decrypto_aes_ctr_init (int /*<<< orphan*/ *,scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  archive_decrypto_aes_ctr_release (int /*<<< orphan*/ *) ; 
 int archive_hmac_sha1_init (int /*<<< orphan*/ *,scalar_t__ const*,size_t) ; 
 int archive_pbkdf2_sha1 (char const*,int /*<<< orphan*/ ,void const*,size_t,int,scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (scalar_t__ const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int zip_alloc_decryption_buffer (struct archive_read*) ; 

__attribute__((used)) static int
init_WinZip_AES_decryption(struct archive_read *a)
{
	struct zip *zip = (struct zip *)(a->format->data);
	const void *p;
	const uint8_t *pv;
	size_t key_len, salt_len;
	uint8_t derived_key[MAX_DERIVED_KEY_BUF_SIZE];
	int retry;
	int r;

	if (zip->cctx_valid || zip->hctx_valid)
		return (ARCHIVE_OK);

	switch (zip->entry->aes_extra.strength) {
	case 1: salt_len = 8;  key_len = 16; break;
	case 2: salt_len = 12; key_len = 24; break;
	case 3: salt_len = 16; key_len = 32; break;
	default: goto corrupted;
	}
	p = __archive_read_ahead(a, salt_len + 2, NULL);
	if (p == NULL)
		goto truncated;

	for (retry = 0;; retry++) {
		const char *passphrase;

		passphrase = __archive_read_next_passphrase(a);
		if (passphrase == NULL) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    (retry > 0)?
				"Incorrect passphrase":
				"Passphrase required for this entry");
			return (ARCHIVE_FAILED);
		}
		memset(derived_key, 0, sizeof(derived_key));
		r = archive_pbkdf2_sha1(passphrase, strlen(passphrase),
		    p, salt_len, 1000, derived_key, key_len * 2 + 2);
		if (r != 0) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Decryption is unsupported due to lack of "
			    "crypto library");
			return (ARCHIVE_FAILED);
		}

		/* Check password verification value. */
		pv = ((const uint8_t *)p) + salt_len;
		if (derived_key[key_len * 2] == pv[0] &&
		    derived_key[key_len * 2 + 1] == pv[1])
			break;/* The passphrase is OK. */
		if (retry > 10000) {
			/* Avoid infinity loop. */
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Too many incorrect passphrases");
			return (ARCHIVE_FAILED);
		}
	}

	r = archive_decrypto_aes_ctr_init(&zip->cctx, derived_key, key_len);
	if (r != 0) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Decryption is unsupported due to lack of crypto library");
		return (ARCHIVE_FAILED);
	}
	r = archive_hmac_sha1_init(&zip->hctx, derived_key + key_len, key_len);
	if (r != 0) {
		archive_decrypto_aes_ctr_release(&zip->cctx);
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Failed to initialize HMAC-SHA1");
		return (ARCHIVE_FAILED);
	}
	zip->cctx_valid = zip->hctx_valid = 1;
	__archive_read_consume(a, salt_len + 2);
	zip->entry_bytes_remaining -= salt_len + 2 + AUTH_CODE_SIZE;
	if (0 == (zip->entry->zip_flags & ZIP_LENGTH_AT_END)
	    && zip->entry_bytes_remaining < 0)
		goto corrupted;
	zip->entry_compressed_bytes_read += salt_len + 2 + AUTH_CODE_SIZE;
	zip->decrypted_bytes_remaining = 0;

	zip->entry->compression = zip->entry->aes_extra.compression;
	return (zip_alloc_decryption_buffer(a));

truncated:
	archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
	    "Truncated ZIP file data");
	return (ARCHIVE_FATAL);
corrupted:
	archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
	    "Corrupted ZIP file data");
	return (ARCHIVE_FATAL);
}