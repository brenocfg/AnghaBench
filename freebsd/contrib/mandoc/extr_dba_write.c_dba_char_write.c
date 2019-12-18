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
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  ofp ; 
 scalar_t__ putc (int,int /*<<< orphan*/ ) ; 

void
dba_char_write(int c)
{
	if (putc(c, ofp) == EOF)
		err(1, "fputc");
}