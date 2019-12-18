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
typedef  int u8 ;
typedef  int u32 ;
struct crypto_aead {int dummy; } ;
struct aead_request {int /*<<< orphan*/ * iv; scalar_t__ assoclen; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int EINVAL ; 
 int EOVERFLOW ; 
 scalar_t__ cpu_to_be32 (int) ; 
 int crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ccm_init_mac(struct aead_request *req, u8 maciv[], u32 msglen)
{
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	__be32 *n = (__be32 *)&maciv[AES_BLOCK_SIZE - 8];
	u32 l = req->iv[0] + 1;

	/* verify that CCM dimension 'L' is set correctly in the IV */
	if (l < 2 || l > 8)
		return -EINVAL;

	/* verify that msglen can in fact be represented in L bytes */
	if (l < 4 && msglen >> (8 * l))
		return -EOVERFLOW;

	/*
	 * Even if the CCM spec allows L values of up to 8, the Linux cryptoapi
	 * uses a u32 type to represent msglen so the top 4 bytes are always 0.
	 */
	n[0] = 0;
	n[1] = cpu_to_be32(msglen);

	memcpy(maciv, req->iv, AES_BLOCK_SIZE - l);

	/*
	 * Meaning of byte 0 according to CCM spec (RFC 3610/NIST 800-38C)
	 * - bits 0..2	: max # of bytes required to represent msglen, minus 1
	 *                (already set by caller)
	 * - bits 3..5	: size of auth tag (1 => 4 bytes, 2 => 6 bytes, etc)
	 * - bit 6	: indicates presence of authenticate-only data
	 */
	maciv[0] |= (crypto_aead_authsize(aead) - 2) << 2;
	if (req->assoclen)
		maciv[0] |= 0x40;

	memset(&req->iv[AES_BLOCK_SIZE - l], 0, l);
	return 0;
}