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
 int /*<<< orphan*/  TMPINNAME ; 
 int /*<<< orphan*/  TMPOUTNAME ; 
 int /*<<< orphan*/  TMPPATNAME ; 
 int /*<<< orphan*/  TMPREJNAME ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  toutkeep ; 
 int /*<<< orphan*/  trejkeep ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

void
my_exit(int status)
{
	unlink(TMPINNAME);
	if (!toutkeep)
		unlink(TMPOUTNAME);
	if (!trejkeep)
		unlink(TMPREJNAME);
	unlink(TMPPATNAME);
	exit(status);
}