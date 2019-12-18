#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  locale_t ;
struct TYPE_6__ {int _flags; scalar_t__ _file; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FIX_LOCALE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLOCKFILE_CANCELSAFE (TYPE_1__*) ; 
 int /*<<< orphan*/  FUNLOCKFILE_CANCELSAFE () ; 
 int __SNBF ; 
 int __SRW ; 
 int __SWR ; 
 int __sbprintf (TYPE_1__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int __vfprintf (TYPE_1__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int
vfprintf_l(FILE * __restrict fp, locale_t locale, const char * __restrict fmt0,
		va_list ap)
{
	int ret;
	FIX_LOCALE(locale);

	FLOCKFILE_CANCELSAFE(fp);
	/* optimise fprintf(stderr) (and other unbuffered Unix files) */
	if ((fp->_flags & (__SNBF|__SWR|__SRW)) == (__SNBF|__SWR) &&
	    fp->_file >= 0)
		ret = __sbprintf(fp, locale, fmt0, ap);
	else
		ret = __vfprintf(fp, locale, fmt0, ap);
	FUNLOCKFILE_CANCELSAFE();
	return (ret);
}