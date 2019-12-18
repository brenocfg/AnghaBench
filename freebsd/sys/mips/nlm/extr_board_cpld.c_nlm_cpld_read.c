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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int le16toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline
int nlm_cpld_read(uint64_t base, int reg)
{
	uint16_t val;

	val = *(volatile uint16_t *)(long)(base + reg * 2);
	return le16toh(val);
}