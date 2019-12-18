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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (unsigned int) ; 

__attribute__((used)) static void regmap_format_32_be(void *buf, unsigned int val, unsigned int shift)
{
	__be32 *b = buf;

	b[0] = cpu_to_be32(val << shift);
}