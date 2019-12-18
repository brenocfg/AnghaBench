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
struct pkcs7_parse_context {TYPE_1__* msg; } ;
struct TYPE_2__ {size_t data_len; size_t data_hdrlen; void const* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*) ; 

int pkcs7_note_data(void *context, size_t hdrlen,
		    unsigned char tag,
		    const void *value, size_t vlen)
{
	struct pkcs7_parse_context *ctx = context;

	pr_debug("Got data\n");

	ctx->msg->data = value;
	ctx->msg->data_len = vlen;
	ctx->msg->data_hdrlen = hdrlen;
	return 0;
}