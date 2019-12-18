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
typedef  scalar_t__ u_char ;

/* Variables and functions */
 scalar_t__ SSH2_MSG_EXT_INFO ; 
 scalar_t__ SSH2_MSG_SERVICE_ACCEPT ; 
 scalar_t__ SSH2_MSG_SERVICE_REQUEST ; 
 scalar_t__ SSH2_MSG_TRANSPORT_MAX ; 
 scalar_t__ SSH2_MSG_TRANSPORT_MIN ; 

__attribute__((used)) static int
ssh_packet_type_is_kex(u_char type)
{
	return
	    type >= SSH2_MSG_TRANSPORT_MIN &&
	    type <= SSH2_MSG_TRANSPORT_MAX &&
	    type != SSH2_MSG_SERVICE_REQUEST &&
	    type != SSH2_MSG_SERVICE_ACCEPT &&
	    type != SSH2_MSG_EXT_INFO;
}