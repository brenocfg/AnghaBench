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
typedef  int /*<<< orphan*/  pid_t_ ;
typedef  int int_t ;

/* Variables and functions */
 int /*<<< orphan*/  STRACE (char*,int,int /*<<< orphan*/ ) ; 

int_t sys_getpriority(int_t which, pid_t_ who) {
    STRACE("getpriority(%d, %d)", which, who);
    return 20;
}