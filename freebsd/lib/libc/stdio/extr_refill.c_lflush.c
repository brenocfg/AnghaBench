#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int _flags; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FLOCKFILE_CANCELSAFE (TYPE_1__*) ; 
 int /*<<< orphan*/  FUNLOCKFILE_CANCELSAFE () ; 
 int __SLBF ; 
 int __SWR ; 
 int __sflush (TYPE_1__*) ; 

__attribute__((used)) static int
lflush(FILE *fp)
{
	int	ret = 0;

	if ((fp->_flags & (__SLBF|__SWR)) == (__SLBF|__SWR)) {
		FLOCKFILE_CANCELSAFE(fp);
		ret = __sflush(fp);
		FUNLOCKFILE_CANCELSAFE();
	}
	return (ret);
}