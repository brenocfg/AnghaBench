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
struct pkcs7_parse_context {int /*<<< orphan*/ * certs; int /*<<< orphan*/ ** ppcerts; TYPE_1__* msg; } ;
struct TYPE_2__ {int /*<<< orphan*/ * certs; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_devel (char*,unsigned char) ; 

int pkcs7_note_certificate_list(void *context, size_t hdrlen,
				unsigned char tag,
				const void *value, size_t vlen)
{
	struct pkcs7_parse_context *ctx = context;

	pr_devel("Got cert list (%02x)\n", tag);

	*ctx->ppcerts = ctx->msg->certs;
	ctx->msg->certs = ctx->certs;
	ctx->certs = NULL;
	ctx->ppcerts = &ctx->certs;
	return 0;
}