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
 int getc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input ; 
 scalar_t__ is_stdin ; 
 int /*<<< orphan*/  lineno ; 
 int /*<<< orphan*/  nextline ; 
 int /*<<< orphan*/  stdin ; 

__attribute__((used)) static int
scanc(void)
{
	int	c;

	if (is_stdin)
		c = getc(stdin);
	else
		c = getc(input);
	lineno = nextline;
	if (c == '\n') {
		nextline++;
	}
	return (c);
}