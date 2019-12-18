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
 int /*<<< orphan*/  err ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 

void
usage(void)
{
	(void)fputs(
	 "usage: pr [+page] [-col] [-adFfmprt] [-e[ch][gap]] [-h header]\n",
	 err);
	(void)fputs(
	 "          [-i[ch][gap]] [-l line] [-n[ch][width]] [-o offset]\n",err);
	(void)fputs(
	 "          [-L locale] [-s[ch]] [-w width] [-] [file ...]\n", err);
}