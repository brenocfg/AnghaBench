#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* __bits; } ;
typedef  TYPE_1__ sigset_t ;

/* Variables and functions */
 int __libc_sigsuspend (TYPE_1__*) ; 
 int /*<<< orphan*/  sigemptyset (TYPE_1__*) ; 

int
sigpause(int mask)
{
	sigset_t set;

	sigemptyset(&set);
	set.__bits[0] = mask;
	return (__libc_sigsuspend(&set));
}