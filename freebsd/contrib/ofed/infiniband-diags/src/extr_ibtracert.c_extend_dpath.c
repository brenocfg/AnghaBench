#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {int cnt; scalar_t__* p; } ;
typedef  TYPE_1__ ib_dr_path_t ;

/* Variables and functions */

__attribute__((used)) static int extend_dpath(ib_dr_path_t * path, int nextport)
{
	if (path->cnt + 2 >= sizeof(path->p))
		return -1;
	++path->cnt;
	path->p[path->cnt] = (uint8_t) nextport;
	return path->cnt;
}