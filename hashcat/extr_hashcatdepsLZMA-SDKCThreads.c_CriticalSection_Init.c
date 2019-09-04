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
typedef  int /*<<< orphan*/  CCriticalSection ;

/* Variables and functions */
 int /*<<< orphan*/  InitializeCriticalSection (int /*<<< orphan*/ *) ; 

WRes CriticalSection_Init(CCriticalSection *p)
{
  /* InitializeCriticalSection can raise only STATUS_NO_MEMORY exception */
  #ifdef _MSC_VER
  __try
  #endif
  {
    InitializeCriticalSection(p);
    /* InitializeCriticalSectionAndSpinCount(p, 0); */
  }
  #ifdef _MSC_VER
  __except (EXCEPTION_EXECUTE_HANDLER) { return 1; }
  #endif
  return 0;
}