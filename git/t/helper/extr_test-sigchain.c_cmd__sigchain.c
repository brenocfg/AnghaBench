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
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  one ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigchain_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  three ; 
 int /*<<< orphan*/  two ; 

int cmd__sigchain(int argc, const char **argv)
{
	sigchain_push(SIGTERM, one);
	sigchain_push(SIGTERM, two);
	sigchain_push(SIGTERM, three);
	raise(SIGTERM);
	return 0;
}