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
struct tpm_parse_context {size_t blob_len; void const* blob; } ;

/* Variables and functions */

int tpm_note_key(void *context, size_t hdrlen,
		   unsigned char tag,
		   const void *value, size_t vlen)
{
	struct tpm_parse_context *ctx = context;

	ctx->blob = value;
	ctx->blob_len = vlen;

	return 0;
}