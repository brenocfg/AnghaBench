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
typedef  void* u8 ;
typedef  void* u64 ;
typedef  int u32 ;
typedef  void* u16 ;

/* Variables and functions */

__attribute__((used)) static void aml_nfw_write_arg(u8 *offset, u32 bit_width, u64 *value)
{
	switch (bit_width) {
	case 8:
		*(u8 *) offset = *value;
		break;
	case 16:
		*(u16 *) offset = *value;
		break;
	case 32:
		*(u32 *) offset = *value;
		break;
	case 64:
		*(u64 *) offset = *value;
		break;
	}
}