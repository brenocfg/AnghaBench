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
typedef  scalar_t__ fpos_t ;
struct TYPE_6__ {int /*<<< orphan*/  _base; } ;
struct TYPE_7__ {scalar_t__ (* _seek ) (int /*<<< orphan*/ ,scalar_t__,int) ;int _flags; scalar_t__ _offset; scalar_t__ _r; TYPE_1__ _bf; int /*<<< orphan*/  _p; int /*<<< orphan*/  _cookie; } ;
typedef  TYPE_2__ FILE ;

/* Variables and functions */
 int EINVAL ; 
 int ESPIPE ; 
 int /*<<< orphan*/  FREEUB (TYPE_2__*) ; 
 scalar_t__ HASUB (TYPE_2__*) ; 
 int SEEK_CUR ; 
 int __SAPP ; 
 int __SEOF ; 
 int __SERR ; 
 int __SOFF ; 
 int __SOPT ; 
 int errno ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,scalar_t__,int) ; 

fpos_t
_sseek(FILE *fp, fpos_t offset, int whence)
{
	fpos_t ret;
	int serrno, errret;

	serrno = errno;
	errno = 0;
	ret = (*fp->_seek)(fp->_cookie, offset, whence);
	errret = errno;
	if (errno == 0)
		errno = serrno;
	/*
	 * Disallow negative seeks per POSIX.
	 * It is needed here to help upper level caller
	 * in the cases it can't detect.
	 */
	if (ret < 0) {
		if (errret == 0) {
			if (offset != 0 || whence != SEEK_CUR) {
				if (HASUB(fp))
					FREEUB(fp);
				fp->_p = fp->_bf._base;
				fp->_r = 0;
				fp->_flags &= ~__SEOF;
			}
			fp->_flags |= __SERR;
			errno = EINVAL;
		} else if (errret == ESPIPE)
			fp->_flags &= ~__SAPP;
		fp->_flags &= ~__SOFF;
		ret = -1;
	} else if (fp->_flags & __SOPT) {
		fp->_flags |= __SOFF;
		fp->_offset = ret;
	}
	return (ret);
}