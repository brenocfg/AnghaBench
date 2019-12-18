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
typedef  int uint8_t ;
struct trad_enc_ctx {long* keys; } ;

/* Variables and functions */
 int /*<<< orphan*/  trad_enc_decrypt_update (struct trad_enc_ctx*,int const*,int,int*,int) ; 
 int /*<<< orphan*/  trad_enc_update_keys (struct trad_enc_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
trad_enc_init(struct trad_enc_ctx *ctx, const char *pw, size_t pw_len,
    const uint8_t *key, size_t key_len, uint8_t *crcchk)
{
	uint8_t header[12];

	if (key_len < 12) {
		*crcchk = 0xff;
		return -1;
	}

	ctx->keys[0] = 305419896L;
	ctx->keys[1] = 591751049L;
	ctx->keys[2] = 878082192L;

	for (;pw_len; --pw_len)
		trad_enc_update_keys(ctx, *pw++);

	trad_enc_decrypt_update(ctx, key, 12, header, 12);
	/* Return the last byte for CRC check. */
	*crcchk = header[11];
	return 0;
}