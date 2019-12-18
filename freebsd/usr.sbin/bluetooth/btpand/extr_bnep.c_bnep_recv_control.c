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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  channel_t ;

/* Variables and functions */
#define  BNEP_CONTROL_COMMAND_NOT_UNDERSTOOD 134 
#define  BNEP_FILTER_MULTI_ADDR_RESPONSE 133 
#define  BNEP_FILTER_MULTI_ADDR_SET 132 
#define  BNEP_FILTER_NET_TYPE_RESPONSE 131 
#define  BNEP_FILTER_NET_TYPE_SET 130 
#define  BNEP_SETUP_CONNECTION_REQUEST 129 
#define  BNEP_SETUP_CONNECTION_RESPONSE 128 
 size_t bnep_recv_control_command_not_understood (int /*<<< orphan*/ *,int*,size_t) ; 
 size_t bnep_recv_filter_multi_addr_rsp (int /*<<< orphan*/ *,int*,size_t) ; 
 size_t bnep_recv_filter_multi_addr_set (int /*<<< orphan*/ *,int*,size_t) ; 
 size_t bnep_recv_filter_net_type_rsp (int /*<<< orphan*/ *,int*,size_t) ; 
 size_t bnep_recv_filter_net_type_set (int /*<<< orphan*/ *,int*,size_t) ; 
 size_t bnep_recv_setup_connection_req (int /*<<< orphan*/ *,int*,size_t) ; 
 size_t bnep_recv_setup_connection_rsp (int /*<<< orphan*/ *,int*,size_t) ; 
 int /*<<< orphan*/  bnep_send_control (int /*<<< orphan*/ *,int const,int) ; 

__attribute__((used)) static size_t
bnep_recv_control(channel_t *chan, uint8_t *ptr, size_t size, bool isext)
{
	uint8_t type;
	size_t len;

	if (size-- < 1)
		return 0;

	type = *ptr++;

	switch (type) {
	case BNEP_CONTROL_COMMAND_NOT_UNDERSTOOD:
		len = bnep_recv_control_command_not_understood(chan, ptr, size);
		break;

	case BNEP_SETUP_CONNECTION_REQUEST:
		if (isext)
			return 0;	/* not allowed in extension headers */

		len = bnep_recv_setup_connection_req(chan, ptr, size);
		break;

	case BNEP_SETUP_CONNECTION_RESPONSE:
		if (isext)
			return 0;	/* not allowed in extension headers */

		len = bnep_recv_setup_connection_rsp(chan, ptr, size);
		break;

	case BNEP_FILTER_NET_TYPE_SET:
		len = bnep_recv_filter_net_type_set(chan, ptr, size);
		break;

	case BNEP_FILTER_NET_TYPE_RESPONSE:
		len = bnep_recv_filter_net_type_rsp(chan, ptr, size);
		break;

	case BNEP_FILTER_MULTI_ADDR_SET:
		len = bnep_recv_filter_multi_addr_set(chan, ptr, size);
		break;

	case BNEP_FILTER_MULTI_ADDR_RESPONSE:
		len = bnep_recv_filter_multi_addr_rsp(chan, ptr, size);
		break;

	default:
		len = 0;
		break;
	}

	if (len == 0)
		bnep_send_control(chan, BNEP_CONTROL_COMMAND_NOT_UNDERSTOOD, type);

	return len;
}