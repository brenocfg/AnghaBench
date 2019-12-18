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
 int SIZE_MAX ; 
 int buffer ; 
 int bufsize ; 
 int current ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  memcpy (int,char const*,size_t) ; 
 int xrealloc (int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
addchars(const char *c, size_t n)
{
	if (n == 0)
		return;
	while (current + n > bufsize) {
		if (bufsize == 0)
			bufsize = 1024;
		else if (bufsize <= SIZE_MAX/2) {
			bufsize *= 2;
		} else {
			errx(1, "size overflow");
		}
		buffer = xrealloc(buffer, bufsize, NULL);
	}
	memcpy(buffer+current, c, n);
	current += n;
}