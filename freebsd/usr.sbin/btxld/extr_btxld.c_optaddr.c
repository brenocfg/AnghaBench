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
typedef  unsigned long uint32_t ;

/* Variables and functions */
 unsigned long MAXU32 ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 unsigned long strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
optaddr(const char *arg)
{
    char *s;
    unsigned long x;

    errno = 0;
    x = strtoul(arg, &s, 0);
    if (errno || !*arg || *s || x > MAXU32)
	errx(1, "%s: Illegal address", arg);
    return x;
}