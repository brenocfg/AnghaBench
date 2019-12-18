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
typedef  int /*<<< orphan*/  gdb_wince_result ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  GDB_SETTHREADCONTEXT ; 
 int getresult (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  puthandle (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putmemory (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ s ; 

__attribute__((used)) static int
set_thread_context (HANDLE h, CONTEXT * c)
{
  gdb_wince_result res;
  if (s < 0)
    return 1;
  puthandle ("SetThreadContext handle", GDB_SETTHREADCONTEXT, h);
  putmemory ("SetThreadContext context", GDB_SETTHREADCONTEXT, c, sizeof (*c));
  return getresult ("SetThreadContext context", GDB_SETTHREADCONTEXT, &res, NULL);
}