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
struct TYPE_4__ {scalar_t__ nice_len; scalar_t__ mode; } ;
typedef  TYPE_1__ lzma_options_lzma ;

/* Variables and functions */
 scalar_t__ LZMA_MODE_FAST ; 
 scalar_t__ LZMA_MODE_NORMAL ; 
 scalar_t__ MATCH_LEN_MAX ; 
 scalar_t__ MATCH_LEN_MIN ; 
 scalar_t__ is_lclppb_valid (TYPE_1__ const*) ; 

__attribute__((used)) static bool
is_options_valid(const lzma_options_lzma *options)
{
	// Validate some of the options. LZ encoder validates nice_len too
	// but we need a valid value here earlier.
	return is_lclppb_valid(options)
			&& options->nice_len >= MATCH_LEN_MIN
			&& options->nice_len <= MATCH_LEN_MAX
			&& (options->mode == LZMA_MODE_FAST
				|| options->mode == LZMA_MODE_NORMAL);
}