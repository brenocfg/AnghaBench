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
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 int flag ; 
 int flag2 ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  thr_usr2 ; 

__attribute__((used)) static void
respected_while_running_handler2(int sig, siginfo_t *info, void *ctx)
{
	if (flag == 1)
		flag = 2;
	flag2 = 1;
	thr_usr2 = pthread_self();
}