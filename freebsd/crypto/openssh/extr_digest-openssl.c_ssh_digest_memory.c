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
typedef  size_t u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct ssh_digest {size_t digest_len; int /*<<< orphan*/  (* mdfunc ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_Digest (void const*,size_t,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int SSH_ERR_LIBCRYPTO_ERROR ; 
 size_t UINT_MAX ; 
 struct ssh_digest* ssh_digest_by_alg (int) ; 
 int /*<<< orphan*/  stub1 () ; 

int
ssh_digest_memory(int alg, const void *m, size_t mlen, u_char *d, size_t dlen)
{
	const struct ssh_digest *digest = ssh_digest_by_alg(alg);
	u_int mdlen;

	if (digest == NULL)
		return SSH_ERR_INVALID_ARGUMENT;
	if (dlen > UINT_MAX)
		return SSH_ERR_INVALID_ARGUMENT;
	if (dlen < digest->digest_len)
		return SSH_ERR_INVALID_ARGUMENT;
	mdlen = dlen;
	if (!EVP_Digest(m, mlen, d, &mdlen, digest->mdfunc(), NULL))
		return SSH_ERR_LIBCRYPTO_ERROR;
	return 0;
}