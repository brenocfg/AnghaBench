#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  process; } ;
typedef  TYPE_1__ process_info_t ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetExitCodeProcess (int /*<<< orphan*/ ,scalar_t__*) ; 

int process_reap(process_info_t *p) {
  DWORD exitCode;
  if (!GetExitCodeProcess(p->process, &exitCode))
    return -1;
  return (int)exitCode;
}