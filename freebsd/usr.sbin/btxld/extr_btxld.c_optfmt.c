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
 unsigned int F_CNT ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 int /*<<< orphan*/ * fmtlist ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
optfmt(const char *arg)
{
    unsigned int i;

    for (i = 0; i < F_CNT && strcmp(arg, fmtlist[i]); i++);
    if (i == F_CNT)
	errx(1, "%s: Unknown format", arg);
    return i;
}