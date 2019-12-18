#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opad ;
typedef  int /*<<< orphan*/  newdigest ;
struct TYPE_4__ {unsigned char* key; int /*<<< orphan*/  sha1ctx; } ;
typedef  TYPE_1__ isc_hmacsha1_t ;

/* Variables and functions */
 int ISC_SHA1_BLOCK_LENGTH ; 
 int ISC_SHA1_DIGESTLENGTH ; 
 int /*<<< orphan*/  OPAD ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  isc_hmacsha1_invalidate (TYPE_1__*) ; 
 int /*<<< orphan*/  isc_sha1_final (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  isc_sha1_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_sha1_update (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

void
isc_hmacsha1_sign(isc_hmacsha1_t *ctx, unsigned char *digest, size_t len) {
	unsigned char opad[ISC_SHA1_BLOCK_LENGTH];
	unsigned char newdigest[ISC_SHA1_DIGESTLENGTH];
	unsigned int i;

	REQUIRE(len <= ISC_SHA1_DIGESTLENGTH);
	isc_sha1_final(&ctx->sha1ctx, newdigest);

	memset(opad, OPAD, sizeof(opad));
	for (i = 0; i < ISC_SHA1_BLOCK_LENGTH; i++)
		opad[i] ^= ctx->key[i];

	isc_sha1_init(&ctx->sha1ctx);
	isc_sha1_update(&ctx->sha1ctx, opad, sizeof(opad));
	isc_sha1_update(&ctx->sha1ctx, newdigest, ISC_SHA1_DIGESTLENGTH);
	isc_sha1_final(&ctx->sha1ctx, newdigest);
	isc_hmacsha1_invalidate(ctx);
	memcpy(digest, newdigest, len);
	memset(newdigest, 0, sizeof(newdigest));
}