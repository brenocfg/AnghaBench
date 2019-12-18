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
typedef  int /*<<< orphan*/  u32 ;
struct chachapoly_ctx {int saltlen; int /*<<< orphan*/ * salt; } ;
struct aead_request {int /*<<< orphan*/ * iv; } ;
typedef  int /*<<< orphan*/  leicb ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int CHACHA_IV_SIZE ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct chachapoly_ctx* crypto_aead_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void chacha_iv(u8 *iv, struct aead_request *req, u32 icb)
{
	struct chachapoly_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	__le32 leicb = cpu_to_le32(icb);

	memcpy(iv, &leicb, sizeof(leicb));
	memcpy(iv + sizeof(leicb), ctx->salt, ctx->saltlen);
	memcpy(iv + sizeof(leicb) + ctx->saltlen, req->iv,
	       CHACHA_IV_SIZE - sizeof(leicb) - ctx->saltlen);
}