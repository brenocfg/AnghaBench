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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint16 ;
struct rpcap_header {int dummy; } ;
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 int rpcap_check_msg_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rpcap_header*,int /*<<< orphan*/ *,char*) ; 
 int rpcap_check_msg_ver (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rpcap_header*,char*) ; 
 int rpcap_recv_msg_header (int /*<<< orphan*/ ,struct rpcap_header*,char*) ; 

__attribute__((used)) static int rpcap_process_msg_header(SOCKET sock, uint8 expected_ver, uint8 request_type, struct rpcap_header *header, char *errbuf)
{
	uint16 errcode;

	if (rpcap_recv_msg_header(sock, header, errbuf) == -1)
	{
		/* Network error. */
		return -1;
	}

	/*
	 * Did the server specify the version we negotiated?
	 */
	if (rpcap_check_msg_ver(sock, expected_ver, header, errbuf) == -1)
		return -1;

	/*
	 * Check the message type.
	 */
	return rpcap_check_msg_type(sock, request_type, header,
	    &errcode, errbuf);
}