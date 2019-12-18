#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WRes ;
struct TYPE_5__ {int /*<<< orphan*/  thread; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ CMtDecThread ;

/* Variables and functions */
 int /*<<< orphan*/  MY_SRes_HRESULT_FROM_WRes (scalar_t__) ; 
 scalar_t__ MtDecThread_CreateEvents (TYPE_1__*) ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  ThreadFunc ; 
 scalar_t__ Thread_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ Thread_WasCreated (int /*<<< orphan*/ *) ; 

__attribute__((used)) static SRes MtDecThread_CreateAndStart(CMtDecThread *t)
{
  WRes wres = MtDecThread_CreateEvents(t);
  // wres = 17; // for test
  if (wres == 0)
  {
    if (Thread_WasCreated(&t->thread))
      return SZ_OK;
    wres = Thread_Create(&t->thread, ThreadFunc, t);
    if (wres == 0)
      return SZ_OK;
  }
  return MY_SRes_HRESULT_FROM_WRes(wres);
}