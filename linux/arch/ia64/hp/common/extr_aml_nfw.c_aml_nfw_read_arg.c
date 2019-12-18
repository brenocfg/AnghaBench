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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static void aml_nfw_read_arg(u8 *offset, u32 bit_width, u64 *value)
{
	switch (bit_width) {
	case 8:
		*value = *(u8 *)offset;
		break;
	case 16:
		*value = *(u16 *)offset;
		break;
	case 32:
		*value = *(u32 *)offset;
		break;
	case 64:
		*value = *(u64 *)offset;
		break;
	}
}