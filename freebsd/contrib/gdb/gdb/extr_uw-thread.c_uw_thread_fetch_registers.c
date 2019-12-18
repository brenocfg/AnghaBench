#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  fpregs; int /*<<< orphan*/  gregs; } ;
struct TYPE_7__ {TYPE_2__ uc_mcontext; } ;
struct thread_map {TYPE_3__ thr_ucontext; } ;
struct thread_info {TYPE_1__* private; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* to_fetch_registers ) (int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  mapp; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRY_BASE (int /*<<< orphan*/ ,int*) ; 
 TYPE_4__ base_ops ; 
 struct thread_info* find_thread_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  read_map (int /*<<< orphan*/ ,struct thread_map*) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  supply_fpregset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  supply_gregset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
uw_thread_fetch_registers (int regno)
{
  int called;
  struct thread_info *info;
  struct thread_map map;

  TRY_BASE (base_ops.to_fetch_registers (regno), &called);
  if (called)
    return;

  if (!(info = find_thread_pid (inferior_ptid)))
    return;
  if (!read_map (info->private->mapp, &map))
    return;

  supply_gregset (&map.thr_ucontext.uc_mcontext.gregs);
  supply_fpregset (&map.thr_ucontext.uc_mcontext.fpregs);
}