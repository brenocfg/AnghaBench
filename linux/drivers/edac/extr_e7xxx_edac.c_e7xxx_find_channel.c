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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  edac_dbg (int,char*) ; 

__attribute__((used)) static inline int e7xxx_find_channel(u16 syndrome)
{
	edac_dbg(3, "\n");

	if ((syndrome & 0xff00) == 0)
		return 0;

	if ((syndrome & 0x00ff) == 0)
		return 1;

	if ((syndrome & 0xf000) == 0 || (syndrome & 0x0f00) == 0)
		return 0;

	return 1;
}