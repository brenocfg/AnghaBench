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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
struct pt_asid {int dummy; } ;

/* Variables and functions */
 int pte_internal ; 
 int pte_invalid ; 
 int pte_nomap ; 

__attribute__((used)) static int image_readmem_callback(uint8_t *buffer, size_t size,
				  const struct pt_asid *asid,
				  uint64_t ip, void *context)
{
	const uint8_t *memory;
	size_t idx;

	(void) asid;

	if (!buffer)
		return -pte_invalid;

	/* We use a constant offset of 0x3000. */
	if (ip < 0x3000ull)
		return -pte_nomap;

	ip -= 0x3000ull;

	memory = (const uint8_t *) context;
	if (!memory)
		return -pte_internal;

	for (idx = 0; idx < size; ++idx)
		buffer[idx] = memory[ip + idx];

	return (int) idx;
}