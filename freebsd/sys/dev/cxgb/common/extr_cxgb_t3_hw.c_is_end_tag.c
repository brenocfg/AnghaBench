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
typedef  int u32 ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int cpu_to_le32 (int) ; 
 int t3_seeprom_read (int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static int is_end_tag(adapter_t * adapter, u32 offset)
{
	u32 read_offset, shift, ret, tmp;
	u8 buf[4];

	read_offset = offset & 0xfffffffc;
	shift = offset & 0x03;

	ret = t3_seeprom_read(adapter, read_offset, &tmp);
	if (ret)
		return ret;
	*((u32 *)buf) = cpu_to_le32(tmp);

	if (buf[shift] == 0x78)
		return 1;
	else
		return 0;
}