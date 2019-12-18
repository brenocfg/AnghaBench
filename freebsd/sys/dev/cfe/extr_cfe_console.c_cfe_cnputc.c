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
struct consdev {int dummy; } ;

/* Variables and functions */
 scalar_t__ cfe_write (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  conhandle ; 

__attribute__((used)) static void
cfe_cnputc(struct consdev *cp, int c)
{
	char cbuf;

	if (c == '\n')
		cfe_cnputc(cp, '\r');

	cbuf = c;
	while (cfe_write(conhandle, &cbuf, 1) == 0)
		continue;
}