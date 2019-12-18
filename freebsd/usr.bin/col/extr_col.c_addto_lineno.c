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
 int INT_MAX ; 
 int INT_MIN ; 
 int /*<<< orphan*/  errx (int,char*) ; 

void
addto_lineno(int *lno, int offset)
{
	if (offset > 0) {
		if (*lno >= INT_MAX - offset)
			errx(1, "too many lines");
	} else {
		if (*lno < INT_MIN - offset)
			errx(1, "too many reverse line feeds");
	}
	*lno += offset;
}