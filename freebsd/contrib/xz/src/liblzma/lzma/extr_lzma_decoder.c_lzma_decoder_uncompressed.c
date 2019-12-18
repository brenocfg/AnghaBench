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
typedef  int /*<<< orphan*/  lzma_vli ;
struct TYPE_2__ {int /*<<< orphan*/  uncompressed_size; } ;
typedef  TYPE_1__ lzma_lzma1_decoder ;

/* Variables and functions */

__attribute__((used)) static void
lzma_decoder_uncompressed(void *coder_ptr, lzma_vli uncompressed_size)
{
	lzma_lzma1_decoder *coder = coder_ptr;
	coder->uncompressed_size = uncompressed_size;
}