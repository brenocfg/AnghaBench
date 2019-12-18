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
struct kvmppc_slb {scalar_t__ tb; } ;

/* Variables and functions */
 int SID_SHIFT ; 
 int SID_SHIFT_1T ; 

__attribute__((used)) static int kvmppc_slb_sid_shift(struct kvmppc_slb *slbe)
{
	return slbe->tb ? SID_SHIFT_1T : SID_SHIFT;
}