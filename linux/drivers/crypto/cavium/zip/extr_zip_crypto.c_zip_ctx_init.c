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
struct zip_operation {void* input; void* output; } ;
struct zip_kernel_ctx {struct zip_operation zip_decomp; struct zip_operation zip_comp; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MAX_INPUT_BUFFER_SIZE ; 
 int /*<<< orphan*/  MAX_OUTPUT_BUFFER_SIZE ; 
 void* zip_data_buf_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zip_data_buf_free (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zip_static_init_zip_ops (struct zip_operation*,int) ; 

__attribute__((used)) static int zip_ctx_init(struct zip_kernel_ctx *zip_ctx, int lzs_flag)
{
	struct zip_operation  *comp_ctx   = &zip_ctx->zip_comp;
	struct zip_operation  *decomp_ctx = &zip_ctx->zip_decomp;

	zip_static_init_zip_ops(comp_ctx, lzs_flag);
	zip_static_init_zip_ops(decomp_ctx, lzs_flag);

	comp_ctx->input  = zip_data_buf_alloc(MAX_INPUT_BUFFER_SIZE);
	if (!comp_ctx->input)
		return -ENOMEM;

	comp_ctx->output = zip_data_buf_alloc(MAX_OUTPUT_BUFFER_SIZE);
	if (!comp_ctx->output)
		goto err_comp_input;

	decomp_ctx->input  = zip_data_buf_alloc(MAX_INPUT_BUFFER_SIZE);
	if (!decomp_ctx->input)
		goto err_comp_output;

	decomp_ctx->output = zip_data_buf_alloc(MAX_OUTPUT_BUFFER_SIZE);
	if (!decomp_ctx->output)
		goto err_decomp_input;

	return 0;

err_decomp_input:
	zip_data_buf_free(decomp_ctx->input, MAX_INPUT_BUFFER_SIZE);

err_comp_output:
	zip_data_buf_free(comp_ctx->output, MAX_OUTPUT_BUFFER_SIZE);

err_comp_input:
	zip_data_buf_free(comp_ctx->input, MAX_INPUT_BUFFER_SIZE);

	return -ENOMEM;
}