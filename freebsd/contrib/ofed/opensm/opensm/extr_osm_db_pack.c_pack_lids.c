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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

__attribute__((used)) static inline void pack_lids(uint16_t min_lid, uint16_t max_lid, char *lid_str)
{
	sprintf(lid_str, "0x%04x 0x%04x", min_lid, max_lid);
}