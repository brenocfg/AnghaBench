#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  alloc; } ;
typedef  scalar_t__ CXzEncHandle ;
typedef  TYPE_1__ CXzEnc ;

/* Variables and functions */
 int /*<<< orphan*/  ISzAlloc_Free (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  XzEnc_Free (TYPE_1__*,int /*<<< orphan*/ ) ; 

void XzEnc_Destroy(CXzEncHandle pp)
{
  CXzEnc *p = (CXzEnc *)pp;
  XzEnc_Free(p, p->alloc);
  ISzAlloc_Free(p->alloc, p);
}