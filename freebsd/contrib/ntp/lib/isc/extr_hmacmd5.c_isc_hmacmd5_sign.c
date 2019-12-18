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
struct TYPE_4__ {unsigned char* key; int /*<<< orphan*/  md5ctx; } ;
typedef  TYPE_1__ isc_hmacmd5_t ;

/* Variables and functions */
 int ISC_MD5_DIGESTLENGTH ; 
 int /*<<< orphan*/  OPAD ; 
 int PADLEN ; 
 int /*<<< orphan*/  isc_hmacmd5_invalidate (TYPE_1__*) ; 
 int /*<<< orphan*/  isc_md5_final (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  isc_md5_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_md5_update (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

void
isc_hmacmd5_sign(isc_hmacmd5_t *ctx, unsigned char *digest) {
	unsigned char opad[PADLEN];
	int i;

	isc_md5_final(&ctx->md5ctx, digest);

	memset(opad, OPAD, sizeof(opad));
	for (i = 0; i < PADLEN; i++)
		opad[i] ^= ctx->key[i];

	isc_md5_init(&ctx->md5ctx);
	isc_md5_update(&ctx->md5ctx, opad, sizeof(opad));
	isc_md5_update(&ctx->md5ctx, digest, ISC_MD5_DIGESTLENGTH);
	isc_md5_final(&ctx->md5ctx, digest);
	isc_hmacmd5_invalidate(ctx);
}