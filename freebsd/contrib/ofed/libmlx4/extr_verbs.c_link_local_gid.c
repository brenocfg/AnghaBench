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
union ibv_gid {scalar_t__ raw; } ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ htobe32 (int) ; 

__attribute__((used)) static int link_local_gid(const union ibv_gid *gid)
{
	uint32_t *tmp = (uint32_t *)gid->raw;
	uint32_t hi = tmp[0];
	uint32_t lo = tmp[1];

	if (hi == htobe32(0xfe800000) && lo == 0)
		return 1;

	return 0;
}