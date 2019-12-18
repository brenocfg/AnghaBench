#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * qword; } ;
struct streebog_state {TYPE_1__ h; } ;
struct shash_desc {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 unsigned int STREEBOG256_DIGEST_SIZE ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 unsigned int crypto_shash_digestsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct streebog_state*,int /*<<< orphan*/ ,int) ; 
 struct streebog_state* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int streebog_init(struct shash_desc *desc)
{
	struct streebog_state *ctx = shash_desc_ctx(desc);
	unsigned int digest_size = crypto_shash_digestsize(desc->tfm);
	unsigned int i;

	memset(ctx, 0, sizeof(struct streebog_state));
	for (i = 0; i < 8; i++) {
		if (digest_size == STREEBOG256_DIGEST_SIZE)
			ctx->h.qword[i] = cpu_to_le64(0x0101010101010101ULL);
	}
	return 0;
}