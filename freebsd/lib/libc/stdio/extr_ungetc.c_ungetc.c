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
 int /*<<< orphan*/  ORIENT (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  __sdidinit ; 
 int /*<<< orphan*/  __sinit () ; 
 int __ungetc (int,int /*<<< orphan*/ *) ; 

int
ungetc(int c, FILE *fp)
{
	int ret;

	if (!__sdidinit)
		__sinit();
	FLOCKFILE_CANCELSAFE(fp);
	ORIENT(fp, -1);
	ret = __ungetc(c, fp);
	FUNLOCKFILE_CANCELSAFE();
	return (ret);
}