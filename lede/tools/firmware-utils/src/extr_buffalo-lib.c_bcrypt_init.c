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
struct bcrypt_ctx {unsigned char* state; unsigned long state_len; int /*<<< orphan*/  j; int /*<<< orphan*/  i; } ;

/* Variables and functions */
 unsigned char* malloc (unsigned long) ; 

int bcrypt_init(struct bcrypt_ctx *ctx, void *key, int keylen,
		unsigned long state_len)
{
	unsigned char *state;
	unsigned char *p = key;
	unsigned long i, j;
	unsigned long k = 0;

	state = malloc(state_len);
	if (state == NULL)
		return -1;

	ctx->i = 0;
	ctx->j = 0;
	ctx->state = state;
	ctx->state_len = state_len;

	for (i = 0; i < state_len; i++)
		state[i] = i;

	for(i = 0, j = 0; i < state_len; i++, j = (j + 1) % keylen) {
		unsigned char t;

		t = state[i];
		k = (k + p[j] + t) % state_len;
		state[i] = state[k];
		state[k] = t;
	}

	return 0;
}