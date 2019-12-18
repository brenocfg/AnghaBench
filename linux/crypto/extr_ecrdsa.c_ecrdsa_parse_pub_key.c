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
struct ecrdsa_ctx {size_t key_len; void const* key; } ;

/* Variables and functions */

int ecrdsa_parse_pub_key(void *context, size_t hdrlen, unsigned char tag,
			 const void *value, size_t vlen)
{
	struct ecrdsa_ctx *ctx = context;

	ctx->key = value;
	ctx->key_len = vlen;
	return 0;
}