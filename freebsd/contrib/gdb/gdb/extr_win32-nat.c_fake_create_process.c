#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  hThread; } ;
struct TYPE_5__ {TYPE_1__ CreateThread; } ;
struct TYPE_6__ {TYPE_2__ u; int /*<<< orphan*/  dwThreadId; int /*<<< orphan*/  dwProcessId; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OpenProcess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCESS_ALL_ACCESS ; 
 int /*<<< orphan*/  child_add_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ current_event ; 
 int /*<<< orphan*/  current_process_handle ; 
 int /*<<< orphan*/  current_thread ; 
 int /*<<< orphan*/  main_thread_id ; 

DWORD
fake_create_process (void)
{
  current_process_handle = OpenProcess (PROCESS_ALL_ACCESS, FALSE,
					current_event.dwProcessId);
  main_thread_id = current_event.dwThreadId;
  current_thread = child_add_thread (main_thread_id,
				     current_event.u.CreateThread.hThread);
  return main_thread_id;
}