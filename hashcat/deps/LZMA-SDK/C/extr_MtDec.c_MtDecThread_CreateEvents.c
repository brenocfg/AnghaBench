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
typedef  scalar_t__ WRes ;
struct TYPE_3__ {int /*<<< orphan*/  canRead; int /*<<< orphan*/  canWrite; } ;
typedef  TYPE_1__ CMtDecThread ;

/* Variables and functions */
 scalar_t__ ArEvent_OptCreate_And_Reset (int /*<<< orphan*/ *) ; 
 scalar_t__ SZ_OK ; 

__attribute__((used)) static WRes MtDecThread_CreateEvents(CMtDecThread *t)
{
  WRes wres = ArEvent_OptCreate_And_Reset(&t->canWrite);
  if (wres == 0)
  {
    wres = ArEvent_OptCreate_And_Reset(&t->canRead);
    if (wres == 0)
      return SZ_OK;
  }
  return wres;
}