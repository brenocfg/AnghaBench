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
typedef  int fpos_t ;
struct TYPE_6__ {int /*<<< orphan*/ * _base; } ;
struct TYPE_7__ {int _flags; int _flags2; int _offset; scalar_t__ _ur; scalar_t__ _r; TYPE_1__ _bf; int /*<<< orphan*/ * _p; int /*<<< orphan*/ * _seek; } ;
typedef  TYPE_2__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  EOVERFLOW ; 
 int /*<<< orphan*/  ESPIPE ; 
 scalar_t__ HASUB (TYPE_2__*) ; 
 size_t OFF_MAX ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_END ; 
 int __S2OAP ; 
 int __SAPP ; 
 int __SERR ; 
 int __SOFF ; 
 int __SRD ; 
 int __SWR ; 
 int _sseek (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 

int
_ftello(FILE *fp, fpos_t *offset)
{
	fpos_t pos;
	size_t n;

	if (fp->_seek == NULL) {
		errno = ESPIPE;			/* historic practice */
		return (1);
	}

	/*
	 * Find offset of underlying I/O object, then
	 * adjust for buffered bytes.
	 */
	if (!(fp->_flags & __SRD) && (fp->_flags & __SWR) &&
	    fp->_p != NULL && fp->_p - fp->_bf._base > 0 &&
	    ((fp->_flags & __SAPP) || (fp->_flags2 & __S2OAP))) {
		pos = _sseek(fp, (fpos_t)0, SEEK_END);
		if (pos == -1)
			return (1);
	} else if (fp->_flags & __SOFF)
		pos = fp->_offset;
	else {
		pos = _sseek(fp, (fpos_t)0, SEEK_CUR);
		if (pos == -1)
			return (1);
	}
	if (fp->_flags & __SRD) {
		/*
		 * Reading.  Any unread characters (including
		 * those from ungetc) cause the position to be
		 * smaller than that in the underlying object.
		 */
		if ((pos -= (HASUB(fp) ? fp->_ur : fp->_r)) < 0) {
			fp->_flags |= __SERR;
			errno = EIO;
			return (1);
		}
		if (HASUB(fp))
			pos -= fp->_r;  /* Can be negative at this point. */
	} else if ((fp->_flags & __SWR) && fp->_p != NULL &&
	    (n = fp->_p - fp->_bf._base) > 0) {
		/*
		 * Writing.  Any buffered characters cause the
		 * position to be greater than that in the
		 * underlying object.
		 */
		if (pos > OFF_MAX - n) {
			errno = EOVERFLOW;
			return (1);
		}
		pos += n;
	}
	*offset = pos;
	return (0);
}