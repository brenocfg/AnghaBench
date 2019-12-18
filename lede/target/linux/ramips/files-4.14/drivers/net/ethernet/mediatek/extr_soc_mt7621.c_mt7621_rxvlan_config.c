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
 int /*<<< orphan*/  MT7621_CDMP_EG_CTRL ; 
 int /*<<< orphan*/  fe_w32 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mt7621_rxvlan_config(bool enable)
{
	if (enable)
		fe_w32(1, MT7621_CDMP_EG_CTRL);
	else
		fe_w32(0, MT7621_CDMP_EG_CTRL);
}