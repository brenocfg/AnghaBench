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
struct eeh_pe {int dummy; } ;
struct TYPE_2__ {int (* err_inject ) (struct eeh_pe*,int,int,unsigned long,unsigned long) ;} ;

/* Variables and functions */
 int EEH_ERR_FUNC_MAX ; 
 int EEH_ERR_FUNC_MIN ; 
 int EEH_ERR_TYPE_32 ; 
 int EEH_ERR_TYPE_64 ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 TYPE_1__* eeh_ops ; 
 int stub1 (struct eeh_pe*,int,int,unsigned long,unsigned long) ; 

int eeh_pe_inject_err(struct eeh_pe *pe, int type, int func,
		      unsigned long addr, unsigned long mask)
{
	/* Invalid PE ? */
	if (!pe)
		return -ENODEV;

	/* Unsupported operation ? */
	if (!eeh_ops || !eeh_ops->err_inject)
		return -ENOENT;

	/* Check on PCI error type */
	if (type != EEH_ERR_TYPE_32 && type != EEH_ERR_TYPE_64)
		return -EINVAL;

	/* Check on PCI error function */
	if (func < EEH_ERR_FUNC_MIN || func > EEH_ERR_FUNC_MAX)
		return -EINVAL;

	return eeh_ops->err_inject(pe, type, func, addr, mask);
}