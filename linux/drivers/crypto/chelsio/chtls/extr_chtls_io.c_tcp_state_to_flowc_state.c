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
typedef  int u8 ;

/* Variables and functions */
 int FW_FLOWC_MNEM_TCPSTATE_CLOSEWAIT ; 
 int FW_FLOWC_MNEM_TCPSTATE_CLOSING ; 
 int FW_FLOWC_MNEM_TCPSTATE_ESTABLISHED ; 
 int FW_FLOWC_MNEM_TCPSTATE_FINWAIT1 ; 
 int FW_FLOWC_MNEM_TCPSTATE_FINWAIT2 ; 
 int FW_FLOWC_MNEM_TCPSTATE_LASTACK ; 
#define  TCP_CLOSE_WAIT 133 
#define  TCP_CLOSING 132 
#define  TCP_ESTABLISHED 131 
#define  TCP_FIN_WAIT1 130 
#define  TCP_FIN_WAIT2 129 
#define  TCP_LAST_ACK 128 

__attribute__((used)) static u8 tcp_state_to_flowc_state(u8 state)
{
	switch (state) {
	case TCP_ESTABLISHED:
		return FW_FLOWC_MNEM_TCPSTATE_ESTABLISHED;
	case TCP_CLOSE_WAIT:
		return FW_FLOWC_MNEM_TCPSTATE_CLOSEWAIT;
	case TCP_FIN_WAIT1:
		return FW_FLOWC_MNEM_TCPSTATE_FINWAIT1;
	case TCP_CLOSING:
		return FW_FLOWC_MNEM_TCPSTATE_CLOSING;
	case TCP_LAST_ACK:
		return FW_FLOWC_MNEM_TCPSTATE_LASTACK;
	case TCP_FIN_WAIT2:
		return FW_FLOWC_MNEM_TCPSTATE_FINWAIT2;
	}

	return FW_FLOWC_MNEM_TCPSTATE_ESTABLISHED;
}