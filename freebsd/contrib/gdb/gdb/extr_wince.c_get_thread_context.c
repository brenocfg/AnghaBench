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
struct TYPE_4__ {int /*<<< orphan*/  ContextFlags; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  TYPE_1__ CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  GDB_GETTHREADCONTEXT ; 
 int getresult (char*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putdword (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puthandle (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ s ; 

__attribute__((used)) static int
get_thread_context (HANDLE h, CONTEXT * c)
{
  if (s < 0)
    return 1;
  puthandle ("GetThreadContext handle", GDB_GETTHREADCONTEXT, h);
  putdword ("GetThreadContext flags", GDB_GETTHREADCONTEXT, c->ContextFlags);
  return getresult ("GetThreadContext context", GDB_GETTHREADCONTEXT, c, NULL);
}