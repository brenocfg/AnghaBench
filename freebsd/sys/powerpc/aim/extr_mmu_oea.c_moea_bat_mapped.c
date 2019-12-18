#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_size_t ;
typedef  int vm_paddr_t ;
typedef  int u_int32_t ;
typedef  int u_int ;
struct TYPE_2__ {int batu; int batl; } ;

/* Variables and functions */
 int BAT_EBS ; 
 int BAT_G ; 
 int BAT_I ; 
 int BAT_PBS ; 
 int BAT_PP_RW ; 
 int BAT_Vs ; 
 int EINVAL ; 
 int EPERM ; 
 int ERANGE ; 
 TYPE_1__* battable ; 

__attribute__((used)) static int
moea_bat_mapped(int idx, vm_paddr_t pa, vm_size_t size)
{
	u_int prot;
	u_int32_t start;
	u_int32_t end;
	u_int32_t bat_ble;

	/*
	 * Return immediately if not a valid mapping
	 */
	if (!(battable[idx].batu & BAT_Vs))
		return (EINVAL);

	/*
	 * The BAT entry must be cache-inhibited, guarded, and r/w
	 * so it can function as an i/o page
	 */
	prot = battable[idx].batl & (BAT_I|BAT_G|BAT_PP_RW);
	if (prot != (BAT_I|BAT_G|BAT_PP_RW))
		return (EPERM);

	/*
	 * The address should be within the BAT range. Assume that the
	 * start address in the BAT has the correct alignment (thus
	 * not requiring masking)
	 */
	start = battable[idx].batl & BAT_PBS;
	bat_ble = (battable[idx].batu & ~(BAT_EBS)) | 0x03;
	end = start | (bat_ble << 15) | 0x7fff;

	if ((pa < start) || ((pa + size) > end))
		return (ERANGE);

	return (0);
}