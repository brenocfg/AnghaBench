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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  clearslot (int) ; 
 int /*<<< orphan*/  curprocs ; 
 int findslot (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pids_remove(pid_t pid)
{
	int slot;

	if ((slot = findslot(pid)) < 0)
		return (0);

	clearslot(slot);
	curprocs--;
	return (1);
}