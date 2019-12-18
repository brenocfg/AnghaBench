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
struct trad_enc_ctx {int dummy; } ;

/* Variables and functions */
 int const trad_enc_decrypt_byte (struct trad_enc_ctx*) ; 
 int /*<<< orphan*/  trad_enc_update_keys (struct trad_enc_ctx*,int) ; 

__attribute__((used)) static void
trad_enc_decrypt_update(struct trad_enc_ctx *ctx, const uint8_t *in,
    size_t in_len, uint8_t *out, size_t out_len)
{
	unsigned i, max;

	max = (unsigned)((in_len < out_len)? in_len: out_len);

	for (i = 0; i < max; i++) {
		uint8_t t = in[i] ^ trad_enc_decrypt_byte(ctx);
		out[i] = t;
		trad_enc_update_keys(ctx, t);
	}
}