#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pingpong_dest {int sockfd; int /*<<< orphan*/  srqn; int /*<<< orphan*/  send_psn; int /*<<< orphan*/  send_qpn; int /*<<< orphan*/  recv_qpn; int /*<<< orphan*/  lid; int /*<<< orphan*/  gid; } ;
typedef  int /*<<< orphan*/  gid ;
struct TYPE_2__ {struct pingpong_dest* rem_dest; } ;

/* Variables and functions */
 char* ADDR_FORMAT ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int MSG_SIZE ; 
 int /*<<< orphan*/  MSG_SSCAN ; 
 TYPE_1__ ctx ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  sscanf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  wire_gid_to_gid (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int recv_remote_dest(int sockfd, int index)
{
	struct pingpong_dest *rem_dest;
	char msg[MSG_SIZE];
	char gid[33];
	int n = 0, r;

	while (n < MSG_SIZE) {
		r = read(sockfd, msg + n, MSG_SIZE - n);
		if (r < 0) {
			perror("client read");
			fprintf(stderr,
				"%d/%d: Couldn't read remote address [%d]\n",
				n, MSG_SIZE, index);
			return -1;
		}
		n += r;
	}

	rem_dest = &ctx.rem_dest[index];
	sscanf(msg, MSG_SSCAN, &rem_dest->lid, &rem_dest->recv_qpn,
		&rem_dest->send_qpn, &rem_dest->send_psn, &rem_dest->srqn, gid);

	wire_gid_to_gid(gid, &rem_dest->gid);
	inet_ntop(AF_INET6, &rem_dest->gid, gid, sizeof(gid));
	printf(ADDR_FORMAT, "remote", rem_dest->lid, rem_dest->recv_qpn,
		rem_dest->send_qpn, rem_dest->send_psn, rem_dest->srqn,
		gid);

	rem_dest->sockfd = sockfd;
	return 0;
}