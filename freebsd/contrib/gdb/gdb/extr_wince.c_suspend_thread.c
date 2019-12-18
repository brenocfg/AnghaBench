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
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  GDB_SUSPENDTHREAD ; 
 scalar_t__ getdword (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puthandle (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ s ; 

__attribute__((used)) static int
suspend_thread (HANDLE h)
{
  if (s < 0)
    return 1;
  puthandle ("SuspendThread handle", GDB_SUSPENDTHREAD, h);
  return (int) getdword ("SuspendThread result", GDB_SUSPENDTHREAD);
}