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
 int /*<<< orphan*/  CHILD_ERR_DUP2 ; 
 int /*<<< orphan*/  child_die (int /*<<< orphan*/ ) ; 
 scalar_t__ dup2 (int,int) ; 

__attribute__((used)) static void child_dup2(int fd, int to)
{
	if (dup2(fd, to) < 0)
		child_die(CHILD_ERR_DUP2);
}