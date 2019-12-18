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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GDB_RESUMETHREAD ; 
 int /*<<< orphan*/  ResumeThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gethandle (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putdword (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
resume_thread (int s)
{
  DWORD res;
  HANDLE h = gethandle (L"ResumeThread handle", s, GDB_RESUMETHREAD);
  res = ResumeThread (h);
  putdword (L"ResumeThread result", s, GDB_RESUMETHREAD, res);
}