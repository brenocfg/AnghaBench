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
struct bcrypt_ctx {unsigned char* state; unsigned long state_len; unsigned char i; unsigned char j; } ;

/* Variables and functions */

int bcrypt_process(struct bcrypt_ctx *ctx, unsigned char *src,
		   unsigned char *dst, unsigned long len)
{
	unsigned char *state = ctx->state;
	unsigned long state_len = ctx->state_len;
	unsigned char i, j;
	unsigned long k;

	i = ctx->i;
	j = ctx->j;

	for (k = 0; k < len; k++) {
		unsigned char t;

		i = (i + 1) % state_len;
		j = (j + state[i]) % state_len;
		t = state[j];
		state[j] = state[i];
		state[i] = t;

		dst[k] = src[k] ^ state[(state[i] + state[j]) % state_len];
	}

	ctx->i = i;
	ctx->j = j;

	return len;
}