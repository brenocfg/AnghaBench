#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  locale_t ;
typedef  int /*<<< orphan*/  __va_list ;
struct TYPE_5__ {char* _base; int _size; } ;
struct TYPE_6__ {int _flags; char* _p; int _w; TYPE_1__ _bf; } ;
typedef  TYPE_2__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_2__ FAKE_FILE ; 
 int /*<<< orphan*/  FIX_LOCALE (int /*<<< orphan*/ ) ; 
 int __SALC ; 
 int __SSTR ; 
 int __SWR ; 
 int __vfprintf (TYPE_2__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 

int
vasprintf_l(char **str, locale_t locale, const char *fmt, __va_list ap)
{
	FILE f = FAKE_FILE;
	int ret;
	FIX_LOCALE(locale);

	f._flags = __SWR | __SSTR | __SALC;
	f._bf._base = f._p = malloc(128);
	if (f._bf._base == NULL) {
		*str = NULL;
		errno = ENOMEM;
		return (-1);
	}
	f._bf._size = f._w = 127;		/* Leave room for the NUL */
	ret = __vfprintf(&f, locale, fmt, ap);
	if (ret < 0) {
		free(f._bf._base);
		*str = NULL;
		errno = ENOMEM;
		return (-1);
	}
	*f._p = '\0';
	*str = (char *)f._bf._base;
	return (ret);
}