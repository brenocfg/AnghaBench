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
typedef  int /*<<< orphan*/  uint8_t ;
struct zip {int /*<<< orphan*/  hctx; scalar_t__ hctx_valid; } ;
struct archive_read {int /*<<< orphan*/  archive; TYPE_1__* format; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  AUTH_CODE_SIZE ; 
 void* __archive_read_ahead (struct archive_read*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __archive_read_consume (struct archive_read*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_hmac_sha1_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int memcmp (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check_authentication_code(struct archive_read *a, const void *_p)
{
	struct zip *zip = (struct zip *)(a->format->data);

	/* Check authentication code. */
	if (zip->hctx_valid) {
		const void *p;
		uint8_t hmac[20];
		size_t hmac_len = 20;
		int cmp;

		archive_hmac_sha1_final(&zip->hctx, hmac, &hmac_len);
		if (_p == NULL) {
			/* Read authentication code. */
			p = __archive_read_ahead(a, AUTH_CODE_SIZE, NULL);
			if (p == NULL) {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Truncated ZIP file data");
				return (ARCHIVE_FATAL);
			}
		} else {
			p = _p;
		}
		cmp = memcmp(hmac, p, AUTH_CODE_SIZE);
		__archive_read_consume(a, AUTH_CODE_SIZE);
		if (cmp != 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "ZIP bad Authentication code");
			return (ARCHIVE_WARN);
		}
	}
	return (ARCHIVE_OK);
}