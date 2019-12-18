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
 int TABSIZE ; 
 char* curline ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
printbuf(void)
{
	char c;
	int i;
	int cnt;

#	define TABSIZE 4

	for (i = 0; (c = curline[i]); i++) {
		if (c == '\t') {
			cnt = 8 - (i % TABSIZE);
			c = ' ';
		} else {
			cnt = 1;
		}
		while (cnt--) {
			(void) fputc(c, stderr);
		}
	}
}