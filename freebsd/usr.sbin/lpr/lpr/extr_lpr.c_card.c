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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  tfd ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static void
card(int c, const char *p2)
{
	char buf[BUFSIZ];
	register char *p1 = buf;
	size_t len = 2;

	*p1++ = c;
	while ((c = *p2++) != '\0' && len < sizeof(buf)) {
		*p1++ = (c == '\n') ? ' ' : c;
		len++;
	}
	*p1++ = '\n';
	write(tfd, buf, len);
}