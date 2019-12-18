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
typedef  int /*<<< orphan*/  val ;
typedef  scalar_t__ uint32_t ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  bs_read (int,long,scalar_t__*,int) ; 

int64_t
bus_read_4(int rid, long ofs)
{
	uint32_t val;

	return ((!bs_read(rid, ofs, &val, sizeof(val))) ? -1 : (int64_t)val);
}