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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FLOCKFILE_CANCELSAFE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FUNLOCKFILE_CANCELSAFE () ; 
 int __sgetc (int /*<<< orphan*/ *) ; 

int
fgetc(FILE *fp)
{
	int retval;
	FLOCKFILE_CANCELSAFE(fp);
	/* Orientation set by __sgetc() when buffer is empty. */
	/* ORIENT(fp, -1); */
	retval = __sgetc(fp);
	FUNLOCKFILE_CANCELSAFE();
	return (retval);
}