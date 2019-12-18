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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE ; 

__attribute__((used)) static inline u8 convert_mgmt_class(u8 mgmt_class)
{
	/* Alias IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE to 0 */
	return mgmt_class == IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE ?
		0 : mgmt_class;
}