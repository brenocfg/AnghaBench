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
#define  VCHIQ_MSG_BULK_RX 142 
#define  VCHIQ_MSG_BULK_RX_DONE 141 
#define  VCHIQ_MSG_BULK_TX 140 
#define  VCHIQ_MSG_BULK_TX_DONE 139 
#define  VCHIQ_MSG_CLOSE 138 
#define  VCHIQ_MSG_CONNECT 137 
#define  VCHIQ_MSG_DATA 136 
#define  VCHIQ_MSG_OPEN 135 
#define  VCHIQ_MSG_OPENACK 134 
#define  VCHIQ_MSG_PADDING 133 
#define  VCHIQ_MSG_PAUSE 132 
#define  VCHIQ_MSG_REMOTE_RELEASE 131 
#define  VCHIQ_MSG_REMOTE_USE 130 
#define  VCHIQ_MSG_REMOTE_USE_ACTIVE 129 
#define  VCHIQ_MSG_RESUME 128 

__attribute__((used)) static const char *msg_type_str(unsigned int msg_type)
{
	switch (msg_type) {
	case VCHIQ_MSG_PADDING:       return "PADDING";
	case VCHIQ_MSG_CONNECT:       return "CONNECT";
	case VCHIQ_MSG_OPEN:          return "OPEN";
	case VCHIQ_MSG_OPENACK:       return "OPENACK";
	case VCHIQ_MSG_CLOSE:         return "CLOSE";
	case VCHIQ_MSG_DATA:          return "DATA";
	case VCHIQ_MSG_BULK_RX:       return "BULK_RX";
	case VCHIQ_MSG_BULK_TX:       return "BULK_TX";
	case VCHIQ_MSG_BULK_RX_DONE:  return "BULK_RX_DONE";
	case VCHIQ_MSG_BULK_TX_DONE:  return "BULK_TX_DONE";
	case VCHIQ_MSG_PAUSE:         return "PAUSE";
	case VCHIQ_MSG_RESUME:        return "RESUME";
	case VCHIQ_MSG_REMOTE_USE:    return "REMOTE_USE";
	case VCHIQ_MSG_REMOTE_RELEASE:      return "REMOTE_RELEASE";
	case VCHIQ_MSG_REMOTE_USE_ACTIVE:   return "REMOTE_USE_ACTIVE";
	}
	return "???";
}