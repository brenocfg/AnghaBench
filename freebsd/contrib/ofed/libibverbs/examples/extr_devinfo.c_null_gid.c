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

__attribute__((used)) static int null_gid(union ibv_gid *gid)
{
	return !(gid->raw[8] | gid->raw[9] | gid->raw[10] | gid->raw[11] |
		 gid->raw[12] | gid->raw[13] | gid->raw[14] | gid->raw[15]);
}