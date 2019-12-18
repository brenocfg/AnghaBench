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
 int /*<<< orphan*/  FLOCKFILE_CANCELSAFE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FUNLOCKFILE_CANCELSAFE () ; 
 int __sgetc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 

int
getchar(void)
{
	int retval;
	FLOCKFILE_CANCELSAFE(stdin);
	/* Orientation set by __sgetc() when buffer is empty. */
	/* ORIENT(stdin, -1); */
	retval = __sgetc(stdin);
	FUNLOCKFILE_CANCELSAFE();
	return (retval);
}