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
typedef  int u_char ;

/* Variables and functions */
 int EOF ; 
 int getchar () ; 
 int length ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ ) ; 

size_t
peek(u_char *buf, size_t nbytes)
{
	size_t n, nread;
	int c;

	if (length != -1 && nbytes > (unsigned int)length)
		nbytes = length;
	nread = 0;
	while (nread < nbytes && (c = getchar()) != EOF) {
		*buf++ = c;
		nread++;
	}
	n = nread;
	while (n-- > 0) {
		c = *--buf;
		ungetc(c, stdin);
	}
	return (nread);
}