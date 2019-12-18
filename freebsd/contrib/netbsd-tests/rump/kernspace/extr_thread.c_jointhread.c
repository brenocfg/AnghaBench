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
 int /*<<< orphan*/  kpause (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_exit (int /*<<< orphan*/ ) ; 
 int testit ; 

__attribute__((used)) static void
jointhread(void *arg)
{

	kpause("take5", false, 1, NULL);
	testit = 1;
	kthread_exit(0);
}