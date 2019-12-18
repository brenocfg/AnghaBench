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
struct sram_parameters {unsigned long long sram_offset; unsigned int sram_size; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ kstrtouint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 scalar_t__ kstrtoull (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  sram_offset ; 
 int /*<<< orphan*/  sram_size ; 

__attribute__((used)) static int get_cache_sram_params(struct sram_parameters *sram_params)
{
	unsigned long long addr;
	unsigned int size;

	if (!sram_size || (kstrtouint(sram_size, 0, &size) < 0))
		return -EINVAL;

	if (!sram_offset || (kstrtoull(sram_offset, 0, &addr) < 0))
		return -EINVAL;

	sram_params->sram_offset = addr;
	sram_params->sram_size = size;

	return 0;
}