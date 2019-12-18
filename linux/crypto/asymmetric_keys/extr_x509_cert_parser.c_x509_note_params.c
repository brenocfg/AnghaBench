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
struct x509_parse_context {size_t params_size; void const* params; scalar_t__ key; TYPE_1__* cert; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw_subject; } ;

/* Variables and functions */

int x509_note_params(void *context, size_t hdrlen,
		     unsigned char tag,
		     const void *value, size_t vlen)
{
	struct x509_parse_context *ctx = context;

	/*
	 * AlgorithmIdentifier is used three times in the x509, we should skip
	 * first and ignore third, using second one which is after subject and
	 * before subjectPublicKey.
	 */
	if (!ctx->cert->raw_subject || ctx->key)
		return 0;
	ctx->params = value - hdrlen;
	ctx->params_size = vlen + hdrlen;
	return 0;
}