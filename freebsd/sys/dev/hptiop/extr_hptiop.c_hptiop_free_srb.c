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
struct hpt_iop_srb {struct hpt_iop_srb* next; } ;
struct hpt_iop_hba {struct hpt_iop_srb* srb_list; } ;

/* Variables and functions */

__attribute__((used)) static void hptiop_free_srb(struct hpt_iop_hba *hba, struct hpt_iop_srb *srb)
{
	srb->next = hba->srb_list;
	hba->srb_list = srb;
}