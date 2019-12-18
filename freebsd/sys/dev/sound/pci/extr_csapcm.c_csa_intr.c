#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  channel; } ;
struct TYPE_4__ {int /*<<< orphan*/  channel; } ;
struct csa_info {TYPE_3__ rch; TYPE_2__* binfo; TYPE_1__ pch; } ;
struct TYPE_5__ {int hisr; } ;

/* Variables and functions */
 int HISR_VC0 ; 
 int HISR_VC1 ; 
 int /*<<< orphan*/  chn_intr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
csa_intr(void *p)
{
	struct csa_info *csa = p;

	if ((csa->binfo->hisr & HISR_VC0) != 0)
		chn_intr(csa->pch.channel);
	if ((csa->binfo->hisr & HISR_VC1) != 0)
		chn_intr(csa->rch.channel);
}