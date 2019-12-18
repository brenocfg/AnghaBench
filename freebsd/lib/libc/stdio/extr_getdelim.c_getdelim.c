#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  size_t ssize_t ;
struct TYPE_7__ {scalar_t__ _r; int /*<<< orphan*/  _flags; int /*<<< orphan*/ * _p; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FLOCKFILE_CANCELSAFE (TYPE_1__*) ; 
 int /*<<< orphan*/  FUNLOCKFILE_CANCELSAFE () ; 
 int /*<<< orphan*/  ORIENT (TYPE_1__*,int) ; 
 int /*<<< orphan*/  __SERR ; 
 int /*<<< orphan*/  __sfeof (TYPE_1__*) ; 
 scalar_t__ __srefill (TYPE_1__*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ expandtofit (char**,int,size_t*) ; 
 int /*<<< orphan*/ * memchr (int /*<<< orphan*/ *,int,scalar_t__) ; 
 scalar_t__ sappend (char**,size_t*,size_t*,int /*<<< orphan*/ *,int) ; 

ssize_t
getdelim(char ** __restrict linep, size_t * __restrict linecapp, int delim,
	 FILE * __restrict fp)
{
	u_char *endp;
	size_t linelen;

	FLOCKFILE_CANCELSAFE(fp);
	ORIENT(fp, -1);

	if (linep == NULL || linecapp == NULL) {
		errno = EINVAL;
		goto error;
	}

	if (*linep == NULL)
		*linecapp = 0;

	if (fp->_r <= 0 && __srefill(fp)) {
		/* If fp is at EOF already, we just need space for the NUL. */
		if (!__sfeof(fp) || expandtofit(linep, 1, linecapp))
			goto error;
		(*linep)[0] = '\0';
		linelen = -1;
		goto end;
	}

	linelen = 0;
	while ((endp = memchr(fp->_p, delim, fp->_r)) == NULL) {
		if (sappend(linep, &linelen, linecapp, fp->_p, fp->_r))
			goto error;
		if (__srefill(fp)) {
			if (!__sfeof(fp))
				goto error;
			goto done;	/* hit EOF */
		}
	}
	endp++;	/* snarf the delimiter, too */
	if (sappend(linep, &linelen, linecapp, fp->_p, endp - fp->_p))
		goto error;
	fp->_r -= endp - fp->_p;
	fp->_p = endp;
done:
	/* Invariant: *linep has space for at least linelen+1 bytes. */
	(*linep)[linelen] = '\0';
end:
	FUNLOCKFILE_CANCELSAFE();
	return (linelen);

error:
	fp->_flags |= __SERR;
	linelen = -1;
	goto end;
}