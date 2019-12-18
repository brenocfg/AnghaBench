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
struct pefile_context {int dummy; } ;

/* Variables and functions */
 int asn1_ber_decoder (int /*<<< orphan*/ *,struct pefile_context*,void const*,size_t) ; 
 int /*<<< orphan*/  mscode_decoder ; 
 int /*<<< orphan*/  pr_devel (char*,size_t,unsigned int,void const*) ; 

int mscode_parse(void *_ctx, const void *content_data, size_t data_len,
		 size_t asn1hdrlen)
{
	struct pefile_context *ctx = _ctx;

	content_data -= asn1hdrlen;
	data_len += asn1hdrlen;
	pr_devel("Data: %zu [%*ph]\n", data_len, (unsigned)(data_len),
		 content_data);

	return asn1_ber_decoder(&mscode_decoder, ctx, content_data, data_len);
}