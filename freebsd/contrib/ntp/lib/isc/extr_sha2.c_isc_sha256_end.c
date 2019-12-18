#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int isc_uint8_t ;
typedef  int isc_sha256_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_CTX_cleanup (int*) ; 
 int ISC_SHA256_DIGESTLENGTH ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  isc_sha256_final (int*,int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 void** sha2_hex_digits ; 

char *
isc_sha256_end(isc_sha256_t *context, char buffer[]) {
	isc_uint8_t	digest[ISC_SHA256_DIGESTLENGTH], *d = digest;
	unsigned int	i;

	/* Sanity check: */
	REQUIRE(context != (isc_sha256_t *)0);

	if (buffer != (char*)0) {
		isc_sha256_final(digest, context);

		for (i = 0; i < ISC_SHA256_DIGESTLENGTH; i++) {
			*buffer++ = sha2_hex_digits[(*d & 0xf0) >> 4];
			*buffer++ = sha2_hex_digits[*d & 0x0f];
			d++;
		}
		*buffer = (char)0;
	} else {
#ifdef ISC_PLATFORM_OPENSSLHASH
		EVP_MD_CTX_cleanup(context);
#else
		memset(context, 0, sizeof(*context));
#endif
	}
	memset(digest, 0, ISC_SHA256_DIGESTLENGTH);
	return buffer;
}