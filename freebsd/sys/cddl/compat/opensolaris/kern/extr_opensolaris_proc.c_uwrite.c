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
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  curthread ; 
 size_t proc_writemem (int /*<<< orphan*/ ,int /*<<< orphan*/ *,uintptr_t,void*,size_t) ; 

int
uwrite(proc_t *p, void *kaddr, size_t len, uintptr_t uaddr)
{
	ssize_t n;

	n = proc_writemem(curthread, p, uaddr, kaddr, len);
	if (n != len)
		return (ENOMEM);
	return (0);
}