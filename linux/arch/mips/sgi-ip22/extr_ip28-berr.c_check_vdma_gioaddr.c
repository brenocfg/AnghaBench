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
typedef  int u32 ;
struct TYPE_2__ {int gio_dma_trans; int gmaddronly; int gio_dma_sbits; } ;

/* Variables and functions */
 int GIO_ERRMASK ; 
 int gio_err_addr ; 
 int gio_err_stat ; 
 TYPE_1__* sgimc ; 

__attribute__((used)) static int check_vdma_gioaddr(void)
{
	if (gio_err_stat & GIO_ERRMASK) {
		u32 a = sgimc->gio_dma_trans;
		a = (sgimc->gmaddronly & ~a) | (sgimc->gio_dma_sbits & a);
		return gio_err_addr == a;
	}
	return 0;
}