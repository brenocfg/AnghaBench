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
 int /*<<< orphan*/  FLOCKFILE_CANCELSAFE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FUNLOCKFILE_CANCELSAFE () ; 
 int /*<<< orphan*/  __sdidinit ; 
 int /*<<< orphan*/  __sinit () ; 
 int _fseeko (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int errno ; 

int
fseeko(FILE *fp, off_t offset, int whence)
{
	int ret;
	int serrno = errno;

	/* make sure stdio is set up */
	if (!__sdidinit)
		__sinit();

	FLOCKFILE_CANCELSAFE(fp);
	ret = _fseeko(fp, offset, whence, 0);
	FUNLOCKFILE_CANCELSAFE();
	if (ret == 0)
		errno = serrno;
	return (ret);
}