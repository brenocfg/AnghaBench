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

/* Variables and functions */
 int /*<<< orphan*/  __decompress (scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ _compressed_end ; 
 scalar_t__ _compressed_start ; 
 scalar_t__ decompress_offset ; 
 int /*<<< orphan*/  error ; 

void *decompress_kernel(void)
{
	void *output = (void *)decompress_offset;

	__decompress(_compressed_start, _compressed_end - _compressed_start,
		     NULL, NULL, output, 0, NULL, error);
	return output;
}