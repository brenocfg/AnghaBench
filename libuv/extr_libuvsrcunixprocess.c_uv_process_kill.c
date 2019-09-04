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
struct TYPE_3__ {int /*<<< orphan*/  pid; } ;
typedef  TYPE_1__ uv_process_t ;

/* Variables and functions */
 int uv_kill (int /*<<< orphan*/ ,int) ; 

int uv_process_kill(uv_process_t* process, int signum) {
  return uv_kill(process->pid, signum);
}