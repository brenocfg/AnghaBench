#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pkcs7_parse_context {TYPE_2__* sinfo; } ;
struct TYPE_4__ {TYPE_1__* sig; } ;
struct TYPE_3__ {size_t s_size; int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kmemdup (void const*,size_t,int /*<<< orphan*/ ) ; 

int pkcs7_sig_note_signature(void *context, size_t hdrlen,
			     unsigned char tag,
			     const void *value, size_t vlen)
{
	struct pkcs7_parse_context *ctx = context;

	ctx->sinfo->sig->s = kmemdup(value, vlen, GFP_KERNEL);
	if (!ctx->sinfo->sig->s)
		return -ENOMEM;

	ctx->sinfo->sig->s_size = vlen;
	return 0;
}