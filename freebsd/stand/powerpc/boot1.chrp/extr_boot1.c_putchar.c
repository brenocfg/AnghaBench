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
 int /*<<< orphan*/  ofw_write (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stdouth ; 

__attribute__((used)) static int
putchar(char c, void *arg)
{
	char buf;

	if (c == '\n') {
		buf = '\r';
		ofw_write(stdouth, &buf, 1);
	}
	buf = c;
	ofw_write(stdouth, &buf, 1);
	return (1);
}