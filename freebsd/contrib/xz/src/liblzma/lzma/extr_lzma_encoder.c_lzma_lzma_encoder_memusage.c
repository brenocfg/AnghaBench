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
typedef  scalar_t__ const uint64_t ;
typedef  int /*<<< orphan*/  lzma_lzma1_encoder ;
typedef  int /*<<< orphan*/  lzma_lz_options ;

/* Variables and functions */
 scalar_t__ const UINT64_MAX ; 
 int /*<<< orphan*/  is_options_valid (void const*) ; 
 scalar_t__ lzma_lz_encoder_memusage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_lz_options (int /*<<< orphan*/ *,void const*) ; 

extern uint64_t
lzma_lzma_encoder_memusage(const void *options)
{
	if (!is_options_valid(options))
		return UINT64_MAX;

	lzma_lz_options lz_options;
	set_lz_options(&lz_options, options);

	const uint64_t lz_memusage = lzma_lz_encoder_memusage(&lz_options);
	if (lz_memusage == UINT64_MAX)
		return UINT64_MAX;

	return (uint64_t)(sizeof(lzma_lzma1_encoder)) + lz_memusage;
}