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
typedef  int /*<<< orphan*/  LINENUM ;

/* Variables and functions */
 char* ifetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofp ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_line(LINENUM line, bool write_newline)
{
	char	*s;

	s = ifetch(line, 0);
	if (s == NULL)
		return;
	/* Note: string is not NUL terminated. */
	for (; *s != '\n'; s++)
		putc(*s, ofp);
	if (write_newline)
		putc('\n', ofp);
}