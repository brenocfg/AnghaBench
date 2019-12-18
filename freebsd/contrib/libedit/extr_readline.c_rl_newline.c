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
 int rl_insert (int,char) ; 

int
rl_newline(int count __attribute__((__unused__)),
    int c __attribute__((__unused__)))
{
	/*
	 * Readline-4.0 appears to ignore the args.
	 */
	return rl_insert(1, '\n');
}