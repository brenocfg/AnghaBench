#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opad ;
typedef  int /*<<< orphan*/  newdigest ;
struct TYPE_3__ {unsigned char* key; int /*<<< orphan*/  sha384ctx; } ;
typedef  TYPE_1__ isc_hmacsha384_t ;

/* Variables and functions */
 int ISC_SHA384_BLOCK_LENGTH ; 
 int ISC_SHA384_DIGESTLENGTH ; 
 int /*<<< orphan*/  OPAD ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  isc_sha384_final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_sha384_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_sha384_update (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

void
isc_hmacsha384_sign(isc_hmacsha384_t *ctx, unsigned char *digest, size_t len) {
	unsigned char opad[ISC_SHA384_BLOCK_LENGTH];
	unsigned char newdigest[ISC_SHA384_DIGESTLENGTH];
	unsigned int i;

	REQUIRE(len <= ISC_SHA384_DIGESTLENGTH);
	isc_sha384_final(newdigest, &ctx->sha384ctx);

	memset(opad, OPAD, sizeof(opad));
	for (i = 0; i < ISC_SHA384_BLOCK_LENGTH; i++)
		opad[i] ^= ctx->key[i];

	isc_sha384_init(&ctx->sha384ctx);
	isc_sha384_update(&ctx->sha384ctx, opad, sizeof(opad));
	isc_sha384_update(&ctx->sha384ctx, newdigest, ISC_SHA384_DIGESTLENGTH);
	isc_sha384_final(newdigest, &ctx->sha384ctx);
	memcpy(digest, newdigest, len);
	memset(newdigest, 0, sizeof(newdigest));
}