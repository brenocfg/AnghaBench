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
struct x509_parse_context {TYPE_1__* cert; } ;
struct TYPE_2__ {size_t raw_issuer_size; int /*<<< orphan*/  issuer; void const* raw_issuer; } ;

/* Variables and functions */
 int x509_fabricate_name (struct x509_parse_context*,size_t,unsigned char,int /*<<< orphan*/ *,size_t) ; 

int x509_note_issuer(void *context, size_t hdrlen,
		     unsigned char tag,
		     const void *value, size_t vlen)
{
	struct x509_parse_context *ctx = context;
	ctx->cert->raw_issuer = value;
	ctx->cert->raw_issuer_size = vlen;
	return x509_fabricate_name(ctx, hdrlen, tag, &ctx->cert->issuer, vlen);
}