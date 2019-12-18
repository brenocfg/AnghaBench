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
struct pkcs7_parse_context {size_t raw_skid_size; void const* raw_skid; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_devel (char*,unsigned char,size_t,unsigned int,void const*) ; 

int pkcs7_sig_note_skid(void *context, size_t hdrlen,
			unsigned char tag,
			const void *value, size_t vlen)
{
	struct pkcs7_parse_context *ctx = context;

	pr_devel("SKID: %02x %zu [%*ph]\n", tag, vlen, (unsigned)vlen, value);

	ctx->raw_skid = value;
	ctx->raw_skid_size = vlen;
	return 0;
}