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
 int /*<<< orphan*/  intbuf ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int quit ; 
 int /*<<< orphan*/  raw () ; 

__attribute__((used)) static void
intcopy(int signo)
{
	raw();
	quit = 1;
	longjmp(intbuf, 1);
}