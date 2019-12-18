#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  __copy_oldmem_page (unsigned long,char*,size_t,unsigned long,int,int) ; 

ssize_t copy_oldmem_page(unsigned long pfn, char *buf, size_t csize,
			 unsigned long offset, int userbuf)
{
	return __copy_oldmem_page(pfn, buf, csize, offset, userbuf, false);
}