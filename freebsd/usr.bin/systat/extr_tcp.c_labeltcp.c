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
 int /*<<< orphan*/  L (int,char*) ; 
 int /*<<< orphan*/  R (int,char*) ; 
 int /*<<< orphan*/  wclrtoeol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wnd ; 

void
labeltcp(void)
{
	wmove(wnd, 0, 0); wclrtoeol(wnd);
#define L(row, str) mvwprintw(wnd, row, 13, str)
#define R(row, str) mvwprintw(wnd, row, 51, str);
	L(0, "TCP Connections");		R(0, "TCP Packets");
	L(1, "connections initiated");		R(1, "total packets sent");
	L(2, "connections accepted");		R(2, "- data");
	L(3, "connections established");	R(3, "- data (retransmit by dupack)");
	L(4, "connections dropped");		R(4, "- data (retransmit by sack)");
	L(5, "- in embryonic state");		R(5, "- ack-only");
	L(6, "- on retransmit timeout");	R(6, "- window probes");
	L(7, "- by keepalive");			R(7, "- window updates");
	L(8, "- from listen queue");		R(8, "- urgent data only");
						R(9, "- control");
						R(10, "- resends by PMTU discovery");
	L(11, "TCP Timers");			R(11, "total packets received");
	L(12, "potential rtt updates");		R(12, "- in sequence");
	L(13, "- successful");			R(13, "- completely duplicate");
	L(14, "delayed acks sent");		R(14, "- with some duplicate data");
	L(15, "retransmit timeouts");		R(15, "- out-of-order");
	L(16, "persist timeouts");		R(16, "- duplicate acks");
	L(17, "keepalive probes");		R(17, "- acks");
	L(18, "- timeouts");			R(18, "- window probes");
						R(19, "- window updates");
						R(20, "- bad checksum");
#undef L
#undef R
}