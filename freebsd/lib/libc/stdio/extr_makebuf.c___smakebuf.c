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
struct TYPE_5__ {int _size; void* _base; } ;
struct TYPE_6__ {int _flags; int /*<<< orphan*/  _file; TYPE_1__ _bf; void* _p; void* _nbuf; } ;
typedef  TYPE_2__ FILE ;

/* Variables and functions */
 int __SLBF ; 
 int __SMBF ; 
 int __SNBF ; 
 int /*<<< orphan*/  __cleanup ; 
 int __swhatbuf (TYPE_2__*,size_t*,int*) ; 
 int /*<<< orphan*/  _cleanup ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 void* malloc (size_t) ; 

void
__smakebuf(FILE *fp)
{
	void *p;
	int flags;
	size_t size;
	int couldbetty;

	if (fp->_flags & __SNBF) {
		fp->_bf._base = fp->_p = fp->_nbuf;
		fp->_bf._size = 1;
		return;
	}
	flags = __swhatbuf(fp, &size, &couldbetty);
	if ((p = malloc(size)) == NULL) {
		fp->_flags |= __SNBF;
		fp->_bf._base = fp->_p = fp->_nbuf;
		fp->_bf._size = 1;
		return;
	}
	__cleanup = _cleanup;
	flags |= __SMBF;
	fp->_bf._base = fp->_p = p;
	fp->_bf._size = size;
	if (couldbetty && isatty(fp->_file))
		flags |= __SLBF;
	fp->_flags |= flags;
}