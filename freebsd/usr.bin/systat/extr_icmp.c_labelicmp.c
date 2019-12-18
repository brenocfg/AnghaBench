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
 int /*<<< orphan*/  B (int,char*) ; 
 int /*<<< orphan*/  L (int,char*) ; 
 int /*<<< orphan*/  R (int,char*) ; 
 int /*<<< orphan*/  wclrtoeol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wnd ; 

void
labelicmp(void)
{
	wmove(wnd, 0, 0); wclrtoeol(wnd);
#define L(row, str) mvwprintw(wnd, row, 10, str)
#define R(row, str) mvwprintw(wnd, row, 45, str);
	L(0, "ICMP Input");		R(0, "ICMP Output");
	L(1, "total messages");		R(1, "total messages");
	L(2, "with bad code");		R(2, "errors generated");
	L(3, "with bad length");	R(3, "suppressed - original too short");
	L(4, "with bad checksum");	R(4, "suppressed - original was ICMP");
	L(5, "with insufficient data");	R(5, "responses sent");
					R(6, "suppressed - multicast echo");
					R(7, "suppressed - multicast tstamp");
	L(9, "Input Histogram");	R(9, "Output Histogram");
#define B(row, str) L(row, str); R(row, str)
	B(10, "echo response");
	B(11, "echo request");
	B(12, "destination unreachable");
	B(13, "redirect");
	B(14, "time-to-live exceeded");
	B(15, "parameter problem");
	L(16, "router advertisement");	R(16, "router solicitation");
#undef L
#undef R
#undef B
}