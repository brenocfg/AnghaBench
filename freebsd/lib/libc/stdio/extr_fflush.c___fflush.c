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
struct TYPE_4__ {int _flags; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int __SRW ; 
 int __SWR ; 
 int __sflush (TYPE_1__*) ; 
 int _fwalk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sflush_locked ; 

int
__fflush(FILE *fp)
{
	int retval;

	if (fp == NULL)
		return (_fwalk(sflush_locked));
	if ((fp->_flags & (__SWR | __SRW)) == 0)
		retval = 0;
	else
		retval = __sflush(fp);
	return (retval);
}