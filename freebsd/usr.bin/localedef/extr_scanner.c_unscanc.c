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
 int /*<<< orphan*/  input ; 
 scalar_t__ is_stdin ; 
 int /*<<< orphan*/  nextline ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ ungetc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yyerror (char*) ; 

__attribute__((used)) static void
unscanc(int c)
{
	if (c == '\n') {
		nextline--;
	}
	if (ungetc(c, is_stdin ? stdin : input) < 0) {
		yyerror("ungetc failed");
	}
}