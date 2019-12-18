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
 int /*<<< orphan*/  get_pathlen (unsigned int,unsigned int,unsigned int,unsigned int*,unsigned int*) ; 

__attribute__((used)) static
bool use_vl1(unsigned src, unsigned dst, unsigned count)
{
	unsigned vl0_len, vl1_len;

	get_pathlen(src, dst, count, &vl0_len, &vl1_len);

	return vl0_len <= vl1_len ? false : true;
}