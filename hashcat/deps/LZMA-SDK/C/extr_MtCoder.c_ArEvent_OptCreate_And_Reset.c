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
typedef  int /*<<< orphan*/  WRes ;
typedef  int /*<<< orphan*/  CEvent ;

/* Variables and functions */
 int /*<<< orphan*/  AutoResetEvent_CreateNotSignaled (int /*<<< orphan*/ *) ; 
 scalar_t__ Event_IsCreated (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Event_Reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static WRes ArEvent_OptCreate_And_Reset(CEvent *p)
{
  if (Event_IsCreated(p))
    return Event_Reset(p);
  return AutoResetEvent_CreateNotSignaled(p);
}