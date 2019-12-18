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
struct TYPE_4__ {int segment; scalar_t__ offset; } ;
struct TYPE_5__ {TYPE_1__ PXEPtr; } ;
typedef  TYPE_2__ pxenv_t ;
typedef  int /*<<< orphan*/  pxe_t ;

/* Variables and functions */
 scalar_t__ PTOV (scalar_t__) ; 
 int /*<<< orphan*/ * pxe_call ; 
 int /*<<< orphan*/ * pxe_p ; 
 TYPE_2__* pxenv_p ; 

void
pxe_enable(void *pxeinfo)
{
	pxenv_p  = (pxenv_t *)pxeinfo;
	pxe_p    = (pxe_t *)PTOV(pxenv_p->PXEPtr.segment * 16 +
				 pxenv_p->PXEPtr.offset);
	pxe_call = NULL;
}