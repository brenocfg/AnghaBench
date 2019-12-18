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
 scalar_t__ EOF ; 
 int /*<<< orphan*/  dba_char_write (char) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ fputs (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofp ; 

void
dba_str_write(const char *str)
{
	if (fputs(str, ofp) == EOF)
		err(1, "fputs");
	dba_char_write('\0');
}