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
 int fid ; 
 int nforce2_fsb_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int nforce2_get(unsigned int cpu)
{
	if (cpu)
		return 0;
	return nforce2_fsb_read(0) * fid * 100;
}