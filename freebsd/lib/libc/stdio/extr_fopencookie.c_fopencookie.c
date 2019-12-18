#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fopencookie_thunk {int /*<<< orphan*/  foc_io; void* foc_cookie; } ;
typedef  int /*<<< orphan*/  cookie_io_functions_t ;
struct TYPE_4__ {int /*<<< orphan*/  _flags; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int O_APPEND ; 
 int /*<<< orphan*/  __SAPP ; 
 int __SRD ; 
 int __SWR ; 
 int __sflags (char const*,int*) ; 
 int /*<<< orphan*/  _fopencookie_close ; 
 int _fopencookie_read (void*,char*,int) ; 
 int /*<<< orphan*/  _fopencookie_seek ; 
 int _fopencookie_write (void*,char const*,int) ; 
 int /*<<< orphan*/  free (struct fopencookie_thunk*) ; 
 TYPE_1__* funopen (struct fopencookie_thunk*,int (*) (void*,char*,int),int (*) (void*,char const*,int),int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fopencookie_thunk* malloc (int) ; 

FILE *
fopencookie(void *cookie, const char *mode, cookie_io_functions_t io_funcs)
{
	int (*readfn)(void *, char *, int);
	int (*writefn)(void *, const char *, int);
	struct fopencookie_thunk *thunk;
	FILE *fp;
	int flags, oflags;

	if ((flags = __sflags(mode, &oflags)) == 0)
		return (NULL);

	thunk = malloc(sizeof(*thunk));
	if (thunk == NULL)
		return (NULL);

	thunk->foc_cookie = cookie;
	thunk->foc_io = io_funcs;

	readfn = _fopencookie_read;
	writefn = _fopencookie_write;
	if (flags == __SWR)
		readfn = NULL;
	else if (flags == __SRD)
		writefn = NULL;

	fp = funopen(thunk, readfn, writefn, _fopencookie_seek,
	    _fopencookie_close);
	if (fp == NULL) {
		free(thunk);
		return (NULL);
	}

	if ((oflags & O_APPEND) != 0)
		fp->_flags |= __SAPP;

	return (fp);
}