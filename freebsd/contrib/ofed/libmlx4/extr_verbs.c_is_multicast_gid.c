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

/* Variables and functions */

__attribute__((used)) static int is_multicast_gid(const union ibv_gid *gid)
{
	return gid->raw[0] == 0xff;
}