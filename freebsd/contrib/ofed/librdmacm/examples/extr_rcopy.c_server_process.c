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
struct msg_hdr {int command; } ;

/* Variables and functions */
#define  CMD_CLOSE 130 
#define  CMD_OPEN 129 
#define  CMD_WRITE 128 
 int /*<<< orphan*/  EINVAL ; 
 int msg_recv_hdr (int,struct msg_hdr*) ; 
 int /*<<< orphan*/  msg_send_resp (int,struct msg_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_close (int,struct msg_hdr*) ; 
 int server_open (int,struct msg_hdr*) ; 
 int server_write (int,struct msg_hdr*) ; 

__attribute__((used)) static void server_process(int rs)
{
	struct msg_hdr msg;
	int ret;

	do {
		ret = msg_recv_hdr(rs, &msg);
		if (ret != sizeof msg)
			break;

		switch (msg.command) {
		case CMD_OPEN:
			ret = server_open(rs, &msg);
			break;
		case CMD_CLOSE:
			server_close(rs, &msg);
			ret = 0;
			break;
		case CMD_WRITE:
			ret = server_write(rs, &msg);
			break;
		default:
			msg_send_resp(rs, &msg, EINVAL);
			ret = -1;
			break;
		}

	} while (!ret);
}