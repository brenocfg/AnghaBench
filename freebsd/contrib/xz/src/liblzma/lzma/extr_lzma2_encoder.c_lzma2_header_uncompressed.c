#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int uncompressed_size; int need_dictionary_reset; int* buf; scalar_t__ buf_pos; } ;
typedef  TYPE_1__ lzma_lzma2_coder ;

/* Variables and functions */
 int LZMA2_CHUNK_MAX ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
lzma2_header_uncompressed(lzma_lzma2_coder *coder)
{
	assert(coder->uncompressed_size > 0);
	assert(coder->uncompressed_size <= LZMA2_CHUNK_MAX);

	// If this is the first chunk, we need to include dictionary
	// reset indicator.
	if (coder->need_dictionary_reset)
		coder->buf[0] = 1;
	else
		coder->buf[0] = 2;

	coder->need_dictionary_reset = false;

	// "Compressed" size
	coder->buf[1] = (coder->uncompressed_size - 1) >> 8;
	coder->buf[2] = (coder->uncompressed_size - 1) & 0xFF;

	// Set the start position for copying.
	coder->buf_pos = 0;
	return;
}