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
struct x509_parse_context {size_t akid_raw_issuer_size; void const* akid_raw_issuer; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int,void const*) ; 

int x509_akid_note_name(void *context, size_t hdrlen,
			unsigned char tag,
			const void *value, size_t vlen)
{
	struct x509_parse_context *ctx = context;

	pr_debug("AKID: name: %*phN\n", (int)vlen, value);

	ctx->akid_raw_issuer = value;
	ctx->akid_raw_issuer_size = vlen;
	return 0;
}