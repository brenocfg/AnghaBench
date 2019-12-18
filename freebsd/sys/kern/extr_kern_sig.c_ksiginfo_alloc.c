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
typedef  int /*<<< orphan*/  ksiginfo_t ;

/* Variables and functions */
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/ * ksiginfo_zone ; 
 scalar_t__ uma_zalloc (int /*<<< orphan*/ *,int) ; 

ksiginfo_t *
ksiginfo_alloc(int wait)
{
	int flags;

	flags = M_ZERO;
	if (! wait)
		flags |= M_NOWAIT;
	if (ksiginfo_zone != NULL)
		return ((ksiginfo_t *)uma_zalloc(ksiginfo_zone, flags));
	return (NULL);
}