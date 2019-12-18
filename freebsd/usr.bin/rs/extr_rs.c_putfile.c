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
 int TRANSPOSE ; 
 char** elem ; 
 int flags ; 
 int nelem ; 
 int ocols ; 
 int orows ; 
 int /*<<< orphan*/  prints (char*,int) ; 
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static void
putfile(void)
{
	char **ep;
	int i, j, k;

	ep = elem;
	if (flags & TRANSPOSE)
		for (i = 0; i < orows; i++) {
			for (j = i; j < nelem; j += orows)
				prints(ep[j], (j - i) / orows);
			putchar('\n');
		}
	else
		for (i = k = 0; i < orows; i++) {
			for (j = 0; j < ocols; j++, k++)
				if (k < nelem)
					prints(ep[k], j);
			putchar('\n');
		}
}