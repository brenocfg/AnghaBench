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
typedef  int dword_t ;

/* Variables and functions */
 int /*<<< orphan*/  STRACE (char*,int) ; 
 int /*<<< orphan*/  do_exit_group (int) ; 

dword_t sys_exit_group(dword_t status) {
    STRACE("exit_group(%d)\n", status);
    do_exit_group(status << 8);
}