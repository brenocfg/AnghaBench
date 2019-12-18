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
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 long strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
optpage(const char *arg, int hi)
{
    char *s;
    long x;

    errno = 0;
    x = strtol(arg, &s, 0);
    if (errno || !*arg || *s || x < 0 || x > hi)
	errx(1, "%s: Illegal page number", arg);
    return x;
}