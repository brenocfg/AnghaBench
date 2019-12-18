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
typedef  scalar_t__ lzma_vli ;

/* Variables and functions */
 scalar_t__ LZMA_VLI_MAX ; 

__attribute__((used)) static inline bool
update_size(lzma_vli *size, lzma_vli add, lzma_vli limit)
{
	if (limit > LZMA_VLI_MAX)
		limit = LZMA_VLI_MAX;

	if (limit < *size || limit - *size < add)
		return true;

	*size += add;

	return false;
}