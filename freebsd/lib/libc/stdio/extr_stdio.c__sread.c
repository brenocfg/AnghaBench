#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int (* _read ) (int /*<<< orphan*/ ,char*,int) ;int _flags; int _offset; int /*<<< orphan*/  _cookie; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int OFF_MAX ; 
 int __SOFF ; 
 int stub1 (int /*<<< orphan*/ ,char*,int) ; 

int
_sread(FILE *fp, char *buf, int n)
{
	int ret;

	ret = (*fp->_read)(fp->_cookie, buf, n);
	if (ret > 0) {
		if (fp->_flags & __SOFF) {
			if (fp->_offset <= OFF_MAX - ret)
				fp->_offset += ret;
			else
				fp->_flags &= ~__SOFF;
		}
	} else if (ret < 0)
		fp->_flags &= ~__SOFF;
	return (ret);
}