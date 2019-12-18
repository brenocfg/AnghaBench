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
struct pkcs8_parse_context {size_t key_size; void const* key; } ;

/* Variables and functions */

int pkcs8_note_key(void *context, size_t hdrlen,
		   unsigned char tag,
		   const void *value, size_t vlen)
{
	struct pkcs8_parse_context *ctx = context;

	ctx->key = value;
	ctx->key_size = vlen;
	return 0;
}