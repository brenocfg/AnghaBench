#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned char* _base; int _size; } ;
struct TYPE_5__ {unsigned char* _ubuf; unsigned char* _p; TYPE_1__ _ub; } ;
typedef  TYPE_2__ FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int EOF ; 
 unsigned char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 unsigned char* reallocarray (unsigned char*,int,int) ; 

__attribute__((used)) static int
__submore(FILE *fp)
{
	int i;
	unsigned char *p;

	if (fp->_ub._base == fp->_ubuf) {
		/*
		 * Get a new buffer (rather than expanding the old one).
		 */
		if ((p = malloc((size_t)BUFSIZ)) == NULL)
			return (EOF);
		fp->_ub._base = p;
		fp->_ub._size = BUFSIZ;
		p += BUFSIZ - sizeof(fp->_ubuf);
		for (i = sizeof(fp->_ubuf); --i >= 0;)
			p[i] = fp->_ubuf[i];
		fp->_p = p;
		return (0);
	}
	i = fp->_ub._size;
	p = reallocarray(fp->_ub._base, i, 2);
	if (p == NULL)
		return (EOF);
	/* no overlap (hence can use memcpy) because we doubled the size */
	(void)memcpy((void *)(p + i), (void *)p, (size_t)i);
	fp->_p = p + i;
	fp->_ub._base = p;
	fp->_ub._size = i * 2;
	return (0);
}