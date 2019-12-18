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
labelsctp(void)
{
	wmove(wnd, 0, 0); wclrtoeol(wnd);
#define L(row, str) mvwprintw(wnd, row, 13, str)
#define R(row, str) mvwprintw(wnd, row, 51, str);
	L(0, "SCTP Associations");		R(0, "SCTP Packets");
	L(1, "associations initiated");		R(1, "packets sent");
	L(2, "associations accepted");		R(2, "packets received");
	L(3, "associations restarted");		R(3, "- out of the blue");
	L(4, "associations terminated");	R(4, "- bad vtag");
	L(5, "associations aborted");		R(5, "- bad crc32c");

	L(7, "SCTP Timers");			R(7, "SCTP Chunks");
	L(8, "init timeouts");			R(8, "control chunks sent");
	L(9, "cookie timeouts");		R(9, "data chunks sent");
	L(10, "data timeouts");			R(10, "- ordered");
	L(11, "delayed sack timeouts");		R(11, "- unordered");
	L(12, "shutdown timeouts");		R(12, "control chunks received");
	L(13, "shutdown-ack timeouts");		R(13, "data chunks received");
	L(14, "shutdown guard timeouts");	R(14, "- ordered");
	L(15, "heartbeat timeouts");		R(15, "- unordered");
	L(16, "path MTU timeouts");
	L(17, "autoclose timeouts");		R(17, "SCTP User Messages");
	L(18, "asconf timeouts");		R(18, "fragmented");
	L(19, "stream reset timeouts");		R(19, "reassembled");
#undef L
#undef R
}