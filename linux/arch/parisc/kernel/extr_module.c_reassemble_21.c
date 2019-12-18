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

__attribute__((used)) static inline int reassemble_21(int as21)
{
	return (((as21 & 0x100000) >> 20) |
		((as21 & 0x0ffe00) >> 8) |
		((as21 & 0x000180) << 7) |
		((as21 & 0x00007c) << 14) |
		((as21 & 0x000003) << 12));
}