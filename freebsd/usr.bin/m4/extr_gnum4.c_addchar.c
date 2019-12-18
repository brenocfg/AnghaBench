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
 int* buffer ; 
 int bufsize ; 
 int current ; 
 int* xrealloc (int*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
addchar(int c)
{
	if (current +1 > bufsize) {
		if (bufsize == 0)
			bufsize = 1024;
		else
			bufsize *= 2;
		buffer = xrealloc(buffer, bufsize, NULL);
	}
	buffer[current++] = c;
}