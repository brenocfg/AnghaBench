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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  CODE_REJ 138 
#define  CONF_ACK 137 
#define  CONF_NAK 136 
#define  CONF_REJ 135 
#define  CONF_REQ 134 
#define  DISC_REQ 133 
#define  ECHO_REPLY 132 
#define  ECHO_REQ 131 
#define  PROTO_REJ 130 
#define  TERM_ACK 129 
#define  TERM_REQ 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static const char *
sppp_cp_type_name(u_char type)
{
	static char buf[12];
	switch (type) {
	case CONF_REQ:   return "conf-req";
	case CONF_ACK:   return "conf-ack";
	case CONF_NAK:   return "conf-nak";
	case CONF_REJ:   return "conf-rej";
	case TERM_REQ:   return "term-req";
	case TERM_ACK:   return "term-ack";
	case CODE_REJ:   return "code-rej";
	case PROTO_REJ:  return "proto-rej";
	case ECHO_REQ:   return "echo-req";
	case ECHO_REPLY: return "echo-reply";
	case DISC_REQ:   return "discard-req";
	}
	snprintf (buf, sizeof(buf), "cp/0x%x", type);
	return buf;
}