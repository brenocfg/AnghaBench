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
typedef  int /*<<< orphan*/  u8 ;
struct hmac_sha1_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  ctx ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1_DIGEST_SIZE ; 
 scalar_t__ TEST_FAIL () ; 
 int /*<<< orphan*/  hmac_sha1_digest (struct hmac_sha1_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hmac_sha1_set_key (struct hmac_sha1_ctx*,size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hmac_sha1_update (struct hmac_sha1_ctx*,size_t const,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  os_memset (struct hmac_sha1_ctx*,int /*<<< orphan*/ ,int) ; 

int hmac_sha1_vector(const u8 *key, size_t key_len, size_t num_elem,
		     const u8 *addr[], const size_t *len, u8 *mac)
{
	struct hmac_sha1_ctx ctx;
	size_t i;

	if (TEST_FAIL())
		return -1;

	hmac_sha1_set_key(&ctx, key_len, key);
	for (i = 0; i < num_elem; i++)
		hmac_sha1_update(&ctx, len[i], addr[i]);
	hmac_sha1_digest(&ctx, SHA1_DIGEST_SIZE, mac);
	os_memset(&ctx, 0, sizeof(ctx));
	return 0;
}