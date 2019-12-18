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
typedef  int /*<<< orphan*/  THREAD_FUNC_TYPE ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ CThread ;

/* Variables and functions */
 scalar_t__ CreateThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HandleToWRes (scalar_t__) ; 
 scalar_t__ _beginthreadex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

WRes Thread_Create(CThread *p, THREAD_FUNC_TYPE func, LPVOID param)
{
  /* Windows Me/98/95: threadId parameter may not be NULL in _beginthreadex/CreateThread functions */
  
  #ifdef UNDER_CE
  
  DWORD threadId;
  *p = CreateThread(0, 0, func, param, 0, &threadId);

  #else

  unsigned threadId;
  *p = (HANDLE)_beginthreadex(NULL, 0, func, param, 0, &threadId);
   
  #endif

  /* maybe we must use errno here, but probably GetLastError() is also OK. */
  return HandleToWRes(*p);
}