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
typedef  int /*<<< orphan*/  lzma_ret ;
typedef  int /*<<< orphan*/  lzma_lz_options ;
struct TYPE_4__ {int /*<<< orphan*/  coder; } ;
typedef  TYPE_1__ lzma_lz_decoder ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  LZMA_PROG_ERROR ; 
 int /*<<< orphan*/  LZMA_VLI_UNKNOWN ; 
 int /*<<< orphan*/  is_lclppb_valid (void const*) ; 
 int /*<<< orphan*/  lzma_decoder_reset (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  lzma_decoder_uncompressed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzma_lzma_decoder_create (TYPE_1__*,int /*<<< orphan*/  const*,void const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_if_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static lzma_ret
lzma_decoder_init(lzma_lz_decoder *lz, const lzma_allocator *allocator,
		const void *options, lzma_lz_options *lz_options)
{
	if (!is_lclppb_valid(options))
		return LZMA_PROG_ERROR;

	return_if_error(lzma_lzma_decoder_create(
			lz, allocator, options, lz_options));

	lzma_decoder_reset(lz->coder, options);
	lzma_decoder_uncompressed(lz->coder, LZMA_VLI_UNKNOWN);

	return LZMA_OK;
}