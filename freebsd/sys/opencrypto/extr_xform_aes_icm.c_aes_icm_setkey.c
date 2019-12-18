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
typedef  int /*<<< orphan*/  u_int8_t ;
struct aes_icm_ctx {int /*<<< orphan*/  ac_ek; int /*<<< orphan*/  ac_nr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/ * KMALLOC (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  M_CRYPTO_DATA ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  rijndaelKeySetupEnc (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int
aes_icm_setkey(u_int8_t **sched, const u_int8_t *key, int len)
{
	struct aes_icm_ctx *ctx;

	if (len != 16 && len != 24 && len != 32)
		return EINVAL;

	*sched = KMALLOC(sizeof(struct aes_icm_ctx), M_CRYPTO_DATA,
	    M_NOWAIT | M_ZERO);
	if (*sched == NULL)
		return ENOMEM;

	ctx = (struct aes_icm_ctx *)*sched;
	ctx->ac_nr = rijndaelKeySetupEnc(ctx->ac_ek, key, len * 8);
	return 0;
}