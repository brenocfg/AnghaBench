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
typedef  int u8 ;
struct wmm_tspec_element {int* ts_info; } ;

/* Variables and functions */

__attribute__((used)) static u8 wmm_ac_get_user_priority(const struct wmm_tspec_element *tspec)
{
	return (tspec->ts_info[1] >> 3) & 0x07;
}