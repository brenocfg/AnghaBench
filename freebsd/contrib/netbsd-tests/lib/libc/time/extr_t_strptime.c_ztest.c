#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* name; int offs; } ;

/* Variables and functions */
 size_t __arraycount (TYPE_1__*) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 TYPE_1__* zt ; 
 int /*<<< orphan*/  ztest1 (char*,char const*,int) ; 

__attribute__((used)) static void
ztest(const char *fmt)
{
	setenv("TZ", "US/Eastern", 1);
#ifndef __FreeBSD__
	ztest1("GMT", fmt, 0);
	ztest1("UTC", fmt, 0);
	ztest1("US/Eastern", fmt, -18000);
#endif
	for (size_t i = 0; i < __arraycount(zt); i++)
		ztest1(zt[i].name, fmt, zt[i].offs);
}