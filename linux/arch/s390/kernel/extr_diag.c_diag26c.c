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
typedef  enum diag26c_sc { ____Placeholder_diag26c_sc } diag26c_sc ;
struct TYPE_2__ {int (* diag26c ) (void*,void*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DIAG_STAT_X26C ; 
 TYPE_1__ diag_dma_ops ; 
 int /*<<< orphan*/  diag_stat_inc (int /*<<< orphan*/ ) ; 
 int stub1 (void*,void*,int) ; 

int diag26c(void *req, void *resp, enum diag26c_sc subcode)
{
	diag_stat_inc(DIAG_STAT_X26C);
	return diag_dma_ops.diag26c(req, resp, subcode);
}