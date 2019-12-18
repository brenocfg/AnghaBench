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
 int /*<<< orphan*/  EXECOP2 (char*,char*,long,long,long) ; 

void exec_opl(long s0, long s1, long iflags)
{
    long res, flags;
    res = s0;
    flags = iflags;
    EXECOP2("l", "k", res, s1, flags);
}