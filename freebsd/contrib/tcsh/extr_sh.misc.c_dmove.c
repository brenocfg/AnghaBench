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
 int dcopy (int,int) ; 
 int /*<<< orphan*/  xclose (int) ; 
 int /*<<< orphan*/  xdup2 (int,int) ; 

int
dmove(int i, int j)
{

    if (i == j || i < 0)
	return (i);
#ifdef HAVE_DUP2
    if (j >= 0) {
	(void) xdup2(i, j);
	if (j != i)
	    xclose(i);
	return (j);
    }
#endif
    j = dcopy(i, j);
    if (j != i)
	xclose(i);
    return (j);
}