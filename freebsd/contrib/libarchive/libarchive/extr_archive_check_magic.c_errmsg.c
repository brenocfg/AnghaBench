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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 size_t strlen (char const*) ; 
 scalar_t__ write (int,char const*,size_t) ; 

__attribute__((used)) static void
errmsg(const char *m)
{
	size_t s = strlen(m);
	ssize_t written;

	while (s > 0) {
		written = write(2, m, strlen(m));
		if (written <= 0)
			return;
		m += written;
		s -= written;
	}
}