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
typedef  scalar_t__ WRes ;
struct TYPE_4__ {int /*<<< orphan*/  startEvent; int /*<<< orphan*/  thread; int /*<<< orphan*/  stop; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ CMtCoderThread ;

/* Variables and functions */
 scalar_t__ ArEvent_OptCreate_And_Reset (int /*<<< orphan*/ *) ; 
 scalar_t__ Event_Set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  MY_SRes_HRESULT_FROM_WRes (scalar_t__) ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  ThreadFunc ; 
 scalar_t__ Thread_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Thread_WasCreated (int /*<<< orphan*/ *) ; 

__attribute__((used)) static SRes MtCoderThread_CreateAndStart(CMtCoderThread *t)
{
  WRes wres = ArEvent_OptCreate_And_Reset(&t->startEvent);
  if (wres == 0)
  {
    t->stop = False;
    if (!Thread_WasCreated(&t->thread))
      wres = Thread_Create(&t->thread, ThreadFunc, t);
    if (wres == 0)
      wres = Event_Set(&t->startEvent);
  }
  if (wres == 0)
    return SZ_OK;
  return MY_SRes_HRESULT_FROM_WRes(wres);
}