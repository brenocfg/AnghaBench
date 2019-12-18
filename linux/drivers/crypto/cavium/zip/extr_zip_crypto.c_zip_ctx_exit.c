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
struct zip_operation {int /*<<< orphan*/  output; int /*<<< orphan*/  input; } ;
struct zip_kernel_ctx {struct zip_operation zip_decomp; struct zip_operation zip_comp; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_INPUT_BUFFER_SIZE ; 
 int /*<<< orphan*/  MAX_OUTPUT_BUFFER_SIZE ; 
 int /*<<< orphan*/  zip_data_buf_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zip_ctx_exit(struct zip_kernel_ctx *zip_ctx)
{
	struct zip_operation  *comp_ctx   = &zip_ctx->zip_comp;
	struct zip_operation  *dec_ctx = &zip_ctx->zip_decomp;

	zip_data_buf_free(comp_ctx->input, MAX_INPUT_BUFFER_SIZE);
	zip_data_buf_free(comp_ctx->output, MAX_OUTPUT_BUFFER_SIZE);

	zip_data_buf_free(dec_ctx->input, MAX_INPUT_BUFFER_SIZE);
	zip_data_buf_free(dec_ctx->output, MAX_OUTPUT_BUFFER_SIZE);
}