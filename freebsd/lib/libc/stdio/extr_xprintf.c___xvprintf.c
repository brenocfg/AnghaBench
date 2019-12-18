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
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_5__ {int _flags; scalar_t__ _file; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int __SNBF ; 
 int __SRW ; 
 int __SWR ; 
 int __v2printf (TYPE_1__*,char const*,unsigned int,int /*<<< orphan*/ ) ; 
 int __v3printf (TYPE_1__*,char const*,unsigned int,int /*<<< orphan*/ ) ; 

int
__xvprintf(FILE *fp, const char *fmt0, va_list ap)
{
	unsigned u;
	const char *p;

	/* Count number of '%' signs handling double '%' signs */
	for (p = fmt0, u = 0; *p; p++) {
		if (*p != '%')
			continue;
		u++;
		if (p[1] == '%')
			p++;
	}

	/* optimise fprintf(stderr) (and other unbuffered Unix files) */
	if ((fp->_flags & (__SNBF|__SWR|__SRW)) == (__SNBF|__SWR) &&
	    fp->_file >= 0)
		return (__v3printf(fp, fmt0, u, ap));
	else
		return (__v2printf(fp, fmt0, u, ap));
}