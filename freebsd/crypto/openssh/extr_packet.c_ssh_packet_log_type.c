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
typedef  int u_char ;

/* Variables and functions */
#define  SSH2_MSG_CHANNEL_DATA 130 
#define  SSH2_MSG_CHANNEL_EXTENDED_DATA 129 
#define  SSH2_MSG_CHANNEL_WINDOW_ADJUST 128 

int
ssh_packet_log_type(u_char type)
{
	switch (type) {
	case SSH2_MSG_CHANNEL_DATA:
	case SSH2_MSG_CHANNEL_EXTENDED_DATA:
	case SSH2_MSG_CHANNEL_WINDOW_ADJUST:
		return 0;
	default:
		return 1;
	}
}