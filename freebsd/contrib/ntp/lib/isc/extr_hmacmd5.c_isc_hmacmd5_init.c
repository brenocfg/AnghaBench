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
typedef  int /*<<< orphan*/  isc_md5_t ;
struct TYPE_3__ {unsigned char* key; int /*<<< orphan*/  md5ctx; } ;
typedef  TYPE_1__ isc_hmacmd5_t ;
typedef  int /*<<< orphan*/  ipad ;

/* Variables and functions */
 int /*<<< orphan*/  IPAD ; 
 int PADLEN ; 
 int /*<<< orphan*/  isc_md5_final (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  isc_md5_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_md5_update (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

void
isc_hmacmd5_init(isc_hmacmd5_t *ctx, const unsigned char *key,
		 unsigned int len)
{
	unsigned char ipad[PADLEN];
	int i;

	memset(ctx->key, 0, sizeof(ctx->key));
	if (len > sizeof(ctx->key)) {
		isc_md5_t md5ctx;
		isc_md5_init(&md5ctx);
		isc_md5_update(&md5ctx, key, len);
		isc_md5_final(&md5ctx, ctx->key);
	} else
		memcpy(ctx->key, key, len);

	isc_md5_init(&ctx->md5ctx);
	memset(ipad, IPAD, sizeof(ipad));
	for (i = 0; i < PADLEN; i++)
		ipad[i] ^= ctx->key[i];
	isc_md5_update(&ctx->md5ctx, ipad, sizeof(ipad));
}