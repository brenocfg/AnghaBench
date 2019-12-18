#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct atm_dev {int dummy; } ;
struct TYPE_4__ {int fdq_wr; int fdq_ed; int fdq_st; } ;
struct TYPE_5__ {scalar_t__ reass_reg; TYPE_1__ rfL; scalar_t__ reass_ram; } ;
typedef  TYPE_2__ IADEV ;

/* Variables and functions */
 scalar_t__ FREEQ_WR_PTR ; 
 TYPE_2__* INPH_IA_DEV (struct atm_dev*) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void free_desc(struct atm_dev *dev, int desc)  
{  
	IADEV *iadev;  
	iadev = INPH_IA_DEV(dev);  
        writew(desc, iadev->reass_ram+iadev->rfL.fdq_wr); 
	iadev->rfL.fdq_wr +=2;
	if (iadev->rfL.fdq_wr > iadev->rfL.fdq_ed)
		iadev->rfL.fdq_wr =  iadev->rfL.fdq_st;  
	writew(iadev->rfL.fdq_wr, iadev->reass_reg+FREEQ_WR_PTR);  
}