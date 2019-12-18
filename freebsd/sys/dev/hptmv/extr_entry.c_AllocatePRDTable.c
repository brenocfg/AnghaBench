#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * pFreePRDLink; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_1__ IAL_ADAPTER_T ;

/* Variables and functions */
 int /*<<< orphan*/  KdPrint (char*) ; 

__attribute__((used)) static PVOID
AllocatePRDTable(IAL_ADAPTER_T *pAdapter)
{
	PVOID ret;
	if (pAdapter->pFreePRDLink) {
		KdPrint(("pAdapter->pFreePRDLink:%p\n",pAdapter->pFreePRDLink));
		ret = pAdapter->pFreePRDLink;
		pAdapter->pFreePRDLink = *(void**)ret;
		return ret;
	}
	return NULL;
}