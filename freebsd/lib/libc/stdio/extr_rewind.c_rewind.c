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
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FLOCKFILE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FUNLOCKFILE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  __sdidinit ; 
 int /*<<< orphan*/  __sinit () ; 
 scalar_t__ _fseeko (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clearerr_unlocked (int /*<<< orphan*/ *) ; 
 int errno ; 

void
rewind(FILE *fp)
{
	int serrno = errno;

	/* make sure stdio is set up */
	if (!__sdidinit)
		__sinit();

	FLOCKFILE(fp);
	if (_fseeko(fp, (off_t)0, SEEK_SET, 1) == 0)
		errno = serrno;
	clearerr_unlocked(fp);	/* POSIX: clear stdio error regardless */
	FUNLOCKFILE(fp);
}