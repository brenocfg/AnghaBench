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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  TS_OPEN ; 
 int rmtcall (char const*,char*) ; 
 int /*<<< orphan*/  rmtstate ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,int) ; 

int
rmtopen(const char *tape, int mode)
{
	char buf[256];

	(void)snprintf(buf, sizeof (buf), "O%.226s\n%d\n", tape, mode);
	rmtstate = TS_OPEN;
	return (rmtcall(tape, buf));
}