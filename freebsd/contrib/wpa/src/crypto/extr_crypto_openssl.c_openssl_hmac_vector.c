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
typedef  int /*<<< orphan*/  HMAC_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  HMAC_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HMAC_CTX_new () ; 
 int HMAC_Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*) ; 
 int HMAC_Init_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_Update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t const) ; 
 scalar_t__ TEST_FAIL () ; 

__attribute__((used)) static int openssl_hmac_vector(const EVP_MD *type, const u8 *key,
			       size_t key_len, size_t num_elem,
			       const u8 *addr[], const size_t *len, u8 *mac,
			       unsigned int mdlen)
{
	HMAC_CTX *ctx;
	size_t i;
	int res;

	if (TEST_FAIL())
		return -1;

	ctx = HMAC_CTX_new();
	if (!ctx)
		return -1;
	res = HMAC_Init_ex(ctx, key, key_len, type, NULL);
	if (res != 1)
		goto done;

	for (i = 0; i < num_elem; i++)
		HMAC_Update(ctx, addr[i], len[i]);

	res = HMAC_Final(ctx, mac, &mdlen);
done:
	HMAC_CTX_free(ctx);

	return res == 1 ? 0 : -1;
}