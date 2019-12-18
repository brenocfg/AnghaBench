#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  check; } ;
struct TYPE_4__ {TYPE_1__ stream_flags; } ;
typedef  TYPE_2__ lzma_stream_coder ;
typedef  int /*<<< orphan*/  lzma_check ;

/* Variables and functions */

__attribute__((used)) static lzma_check
stream_decoder_get_check(const void *coder_ptr)
{
	const lzma_stream_coder *coder = coder_ptr;
	return coder->stream_flags.check;
}