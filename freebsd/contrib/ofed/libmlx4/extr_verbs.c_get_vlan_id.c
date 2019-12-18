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
union ibv_gid {int* raw; } ;
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static uint16_t get_vlan_id(union ibv_gid *gid)
{
	uint16_t vid;
	vid = gid->raw[11] << 8 | gid->raw[12];
	return vid < 0x1000 ? vid : 0xffff;
}