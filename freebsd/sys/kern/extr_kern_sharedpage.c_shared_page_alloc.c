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

/* Variables and functions */
 int shared_page_alloc_locked (int,int) ; 
 int /*<<< orphan*/  shared_page_alloc_sx ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
shared_page_alloc(int size, int align)
{
	int res;

	sx_xlock(&shared_page_alloc_sx);
	res = shared_page_alloc_locked(size, align);
	sx_xunlock(&shared_page_alloc_sx);
	return (res);
}