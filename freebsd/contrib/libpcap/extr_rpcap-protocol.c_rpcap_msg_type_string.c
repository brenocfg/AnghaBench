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
typedef  int uint8 ;

/* Variables and functions */
 int NUM_REPLY_TYPES ; 
 int NUM_REQ_TYPES ; 
 int RPCAP_MSG_IS_REPLY ; 
 char const** replies ; 
 char const** requests ; 

const char *
rpcap_msg_type_string(uint8 type)
{
	if (type & RPCAP_MSG_IS_REPLY) {
		type &= ~RPCAP_MSG_IS_REPLY;
		if (type >= NUM_REPLY_TYPES)
			return NULL;
		return replies[type];
	} else {
		if (type >= NUM_REQ_TYPES)
			return NULL;
		return requests[type];
	}
}