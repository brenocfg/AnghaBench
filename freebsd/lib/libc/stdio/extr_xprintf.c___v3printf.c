#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_7__ {unsigned char* _base; int _size; } ;
struct TYPE_8__ {int _flags; unsigned char* _p; int _w; scalar_t__ _lbfsize; TYPE_1__ _bf; int /*<<< orphan*/  _mbstate; int /*<<< orphan*/  _orientation; int /*<<< orphan*/  _write; int /*<<< orphan*/  _cookie; int /*<<< orphan*/  _file; } ;
typedef  TYPE_2__ FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int EOF ; 
 TYPE_2__ FAKE_FILE ; 
 int __SERR ; 
 int __SNBF ; 
 scalar_t__ __fflush (TYPE_2__*) ; 
 int __v2printf (TYPE_2__*,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__v3printf(FILE *fp, const char *fmt, int pct, va_list ap)
{
	int ret;
	FILE fake = FAKE_FILE;
	unsigned char buf[BUFSIZ];

	/* copy the important variables */
	fake._flags = fp->_flags & ~__SNBF;
	fake._file = fp->_file;
	fake._cookie = fp->_cookie;
	fake._write = fp->_write;
	fake._orientation = fp->_orientation;
	fake._mbstate = fp->_mbstate;

	/* set up the buffer */
	fake._bf._base = fake._p = buf;
	fake._bf._size = fake._w = sizeof(buf);
	fake._lbfsize = 0;	/* not actually used, but Just In Case */

	/* do the work, then copy any error status */
	ret = __v2printf(&fake, fmt, pct, ap);
	if (ret >= 0 && __fflush(&fake))
		ret = EOF;
	if (fake._flags & __SERR)
		fp->_flags |= __SERR;
	return (ret);
}