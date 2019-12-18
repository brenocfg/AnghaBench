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
 int /*<<< orphan*/  NP ; 
 scalar_t__ OBUFSIZ ; 
 scalar_t__ OP ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  UB ; 
 scalar_t__ obufcnt ; 
 int /*<<< orphan*/  oflush () ; 
 char* outbuf ; 
 int* partab ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
putchr(int cc)
{
	char c;

	c = cc;
	if (!NP) {
		c |= partab[c&0177] & 0200;
		if (OP)
			c ^= 0200;
	}
	if (!UB) {
		outbuf[obufcnt++] = c;
		if (obufcnt >= OBUFSIZ)
			oflush();
	} else
		write(STDOUT_FILENO, &c, 1);
}