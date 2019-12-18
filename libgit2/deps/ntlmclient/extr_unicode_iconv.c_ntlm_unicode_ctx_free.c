#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ utf16_to_8; scalar_t__ utf8_to_16; } ;
typedef  TYPE_1__ ntlm_unicode_ctx ;
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  iconv_close (scalar_t__) ; 

void ntlm_unicode_ctx_free(ntlm_unicode_ctx *ctx)
{
	if (!ctx)
		return;

	if (ctx->utf16_to_8 != (iconv_t)-1)
		iconv_close(ctx->utf16_to_8);

	if (ctx->utf8_to_16 != (iconv_t)-1)
		iconv_close(ctx->utf8_to_16);

	free(ctx);
}