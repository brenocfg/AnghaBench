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
typedef  int /*<<< orphan*/  isc_uint8_t ;
typedef  int /*<<< orphan*/  isc_sha256_t ;
typedef  int /*<<< orphan*/  isc_sha224_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_SHA224_DIGESTLENGTH ; 
 int ISC_SHA256_DIGESTLENGTH ; 
 int /*<<< orphan*/  isc_sha256_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
isc_sha224_final(isc_uint8_t digest[], isc_sha224_t *context) {
	isc_uint8_t sha256_digest[ISC_SHA256_DIGESTLENGTH];
	isc_sha256_final(sha256_digest, (isc_sha256_t *)context);
	memcpy(digest, sha256_digest, ISC_SHA224_DIGESTLENGTH);
	memset(sha256_digest, 0, ISC_SHA256_DIGESTLENGTH);
}