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

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ print_exit ; 
 int /*<<< orphan*/  printf (char*,int) ; 

void
option_exits(int exit_code)
{
    if (print_exit)
        printf("\nexit %d\n", exit_code);
    exit(exit_code);
}