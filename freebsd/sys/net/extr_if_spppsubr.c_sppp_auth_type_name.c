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
typedef  int u_short ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  CHAP_CHALLENGE 136 
#define  CHAP_FAILURE 135 
#define  CHAP_RESPONSE 134 
#define  CHAP_SUCCESS 133 
#define  PAP_ACK 132 
#define  PAP_NAK 131 
#define  PAP_REQ 130 
#define  PPP_CHAP 129 
#define  PPP_PAP 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static const char *
sppp_auth_type_name(u_short proto, u_char type)
{
	static char buf[12];
	switch (proto) {
	case PPP_CHAP:
		switch (type) {
		case CHAP_CHALLENGE:	return "challenge";
		case CHAP_RESPONSE:	return "response";
		case CHAP_SUCCESS:	return "success";
		case CHAP_FAILURE:	return "failure";
		}
	case PPP_PAP:
		switch (type) {
		case PAP_REQ:		return "req";
		case PAP_ACK:		return "ack";
		case PAP_NAK:		return "nak";
		}
	}
	snprintf (buf, sizeof(buf), "auth/0x%x", type);
	return buf;
}