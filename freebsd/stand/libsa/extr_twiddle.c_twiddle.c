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
typedef  int u_int ;

/* Variables and functions */
 int globaldiv ; 
 int /*<<< orphan*/  putchar (char) ; 

void
twiddle(u_int callerdiv)
{
	static u_int callercnt, globalcnt, pos;

	callercnt++;
	if (callerdiv > 1 && (callercnt % callerdiv) != 0)
		return;

	globalcnt++;
	if (globaldiv > 1 && (globalcnt % globaldiv) != 0)
		return;

	putchar("|/-\\"[pos++ & 3]);
	putchar('\b');
}