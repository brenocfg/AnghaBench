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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_2__ {int /*<<< orphan*/  dict_size; } ;
typedef  TYPE_1__ lzma_options_lzma ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_DICT_SIZE_MIN ; 
 int /*<<< orphan*/  LZMA_OK ; 
 int UINT32_MAX ; 
 int get_dist_slot (int) ; 
 int my_max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

extern lzma_ret
lzma_lzma2_props_encode(const void *options, uint8_t *out)
{
	const lzma_options_lzma *const opt = options;
	uint32_t d = my_max(opt->dict_size, LZMA_DICT_SIZE_MIN);

	// Round up to the next 2^n - 1 or 2^n + 2^(n - 1) - 1 depending
	// on which one is the next:
	--d;
	d |= d >> 2;
	d |= d >> 3;
	d |= d >> 4;
	d |= d >> 8;
	d |= d >> 16;

	// Get the highest two bits using the proper encoding:
	if (d == UINT32_MAX)
		out[0] = 40;
	else
		out[0] = get_dist_slot(d + 1) - 24;

	return LZMA_OK;
}