#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {unsigned char* _base; int _size; } ;
struct TYPE_7__ {unsigned char* _p; int _w; int _file; TYPE_1__ _bf; int /*<<< orphan*/  _write; struct TYPE_7__* _cookie; int /*<<< orphan*/  _flags; } ;
typedef  TYPE_2__ FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  EMFILE ; 
 int EOF ; 
 TYPE_2__ FAKE_FILE ; 
 int SHRT_MAX ; 
 int /*<<< orphan*/  __SWR ; 
 scalar_t__ __fflush (TYPE_2__*) ; 
 int /*<<< orphan*/  __get_locale () ; 
 int /*<<< orphan*/  __swrite ; 
 int __vfprintf (TYPE_2__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 

int
vdprintf(int fd, const char * __restrict fmt, va_list ap)
{
	FILE f = FAKE_FILE;
	unsigned char buf[BUFSIZ];
	int ret;

	if (fd > SHRT_MAX) {
		errno = EMFILE;
		return (EOF);
	}

	f._p = buf;
	f._w = sizeof(buf);
	f._flags = __SWR;
	f._file = fd;
	f._cookie = &f;
	f._write = __swrite;
	f._bf._base = buf;
	f._bf._size = sizeof(buf);

	if ((ret = __vfprintf(&f, __get_locale(), fmt, ap)) < 0)
		return (ret);

	return (__fflush(&f) ? EOF : ret);
}