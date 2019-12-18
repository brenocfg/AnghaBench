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
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_3__ {unsigned long long starttime; } ;
typedef  TYPE_1__ pid_info_t ;

/* Variables and functions */
 scalar_t__ get_pid_info (int /*<<< orphan*/ ,TYPE_1__*) ; 

unsigned long long get_pid_start_time (pid_t pid) {
  pid_info_t info;
  unsigned long long res = 0;
  if (get_pid_info (pid, &info)) {
    res = info.starttime;
  }

  return res;
}