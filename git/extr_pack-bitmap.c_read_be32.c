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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  result ;

/* Variables and functions */
 int /*<<< orphan*/  get_be32 (unsigned char const*) ; 

__attribute__((used)) static inline uint32_t read_be32(const unsigned char *buffer, size_t *pos)
{
	uint32_t result = get_be32(buffer + *pos);
	(*pos) += sizeof(result);
	return result;
}