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

/* Variables and functions */
 int /*<<< orphan*/  ExitThread (int) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  pthread_exit (void*) ; 

void thrd_exit(int res)
{
#if defined(_TTHREAD_WIN32_)
  ExitThread(res);
#else
  void *pres = malloc(sizeof(int));
  if (pres != NULL)
  {
    *(int*)pres = res;
  }
  pthread_exit(pres);
#endif
}