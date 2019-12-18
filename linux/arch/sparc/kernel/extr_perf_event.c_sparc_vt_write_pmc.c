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
typedef  int u64 ;
struct TYPE_2__ {int (* read_pcr ) (int) ;int /*<<< orphan*/  (* write_pcr ) (int,int) ;int /*<<< orphan*/  (* write_pic ) (int,int) ;} ;

/* Variables and functions */
 int PCR_N4_NTC ; 
 int PCR_N4_OV ; 
 TYPE_1__* pcr_ops ; 
 int stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int,int) ; 
 int /*<<< orphan*/  stub3 (int,int) ; 

__attribute__((used)) static void sparc_vt_write_pmc(int idx, u64 val)
{
	u64 pcr;

	pcr = pcr_ops->read_pcr(idx);
	/* ensure ov and ntc are reset */
	pcr &= ~(PCR_N4_OV | PCR_N4_NTC);

	pcr_ops->write_pic(idx, val & 0xffffffff);

	pcr_ops->write_pcr(idx, pcr);
}