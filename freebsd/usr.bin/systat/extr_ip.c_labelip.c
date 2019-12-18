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
labelip(void)
{
	wmove(wnd, 0, 0); wclrtoeol(wnd);
#define L(row, str) mvwprintw(wnd, row, 10, str)
#define R(row, str) mvwprintw(wnd, row, 45, str);
	L(0, "IP Input");		R(0, "IP Output");
	L(1, "total packets received");	R(1, "total packets sent");
	L(2, "- with bad checksums");	R(2, "- generated locally");
	L(3, "- too short for header");	R(3, "- output drops");
	L(4, "- too short for data");	R(4, "output fragments generated");
	L(5, "- with invalid hlen");	R(5, "- fragmentation failed");
	L(6, "- with invalid length");	R(6, "destinations unreachable");
	L(7, "- with invalid version");	R(7, "packets output via raw IP");
	L(8, "- jumbograms");
	L(9, "total fragments received");	R(9, "UDP Statistics");
	L(10, "- fragments dropped");	R(10, "total input packets");
	L(11, "- fragments timed out");	R(11, "- too short for header");
	L(12, "- packets reassembled ok");	R(12, "- invalid checksum");
	L(13, "packets forwarded");	R(13, "- no checksum");
	L(14, "- unreachable dests");	R(14, "- invalid length");
	L(15, "- redirects generated");	R(15, "- no socket for dest port");
	L(16, "option errors");		R(16, "- no socket for broadcast");
	L(17, "unwanted multicasts");	R(17, "- socket buffer full");
	L(18, "delivered to upper layer");	R(18, "total output packets");
#undef L
#undef R
}