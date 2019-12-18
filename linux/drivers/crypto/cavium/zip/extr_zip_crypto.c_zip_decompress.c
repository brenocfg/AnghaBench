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
typedef  scalar_t__ u8 ;
struct zip_state {int dummy; } ;
struct zip_operation {int ccode; unsigned int input_len; unsigned int output_len; scalar_t__ const* output; scalar_t__* input; } ;
struct zip_kernel_ctx {struct zip_operation zip_decomp; } ;
struct zip_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (struct zip_state*) ; 
 struct zip_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,unsigned int) ; 
 struct zip_device* zip_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zip_get_node_id () ; 
 int zip_inflate (struct zip_operation*,struct zip_state*,struct zip_device*) ; 

__attribute__((used)) static int zip_decompress(const u8 *src, unsigned int slen,
		   u8 *dst, unsigned int *dlen,
		   struct zip_kernel_ctx *zip_ctx)
{
	struct zip_operation  *zip_ops   = NULL;
	struct zip_state      *zip_state;
	struct zip_device     *zip = NULL;
	int ret;

	if (!zip_ctx || !src || !dst || !dlen)
		return -ENOMEM;

	zip = zip_get_device(zip_get_node_id());
	if (!zip)
		return -ENODEV;

	zip_state = kzalloc(sizeof(*zip_state), GFP_ATOMIC);
	if (!zip_state)
		return -ENOMEM;

	zip_ops = &zip_ctx->zip_decomp;
	memcpy(zip_ops->input, src, slen);

	/* Work around for a bug in zlib which needs an extra bytes sometimes */
	if (zip_ops->ccode != 3) /* Not LZS Encoding */
		zip_ops->input[slen++] = 0;

	zip_ops->input_len  = slen;
	zip_ops->output_len = *dlen;

	ret = zip_inflate(zip_ops, zip_state, zip);

	if (!ret) {
		*dlen = zip_ops->output_len;
		memcpy(dst, zip_ops->output, *dlen);
	}
	kfree(zip_state);
	return ret;
}