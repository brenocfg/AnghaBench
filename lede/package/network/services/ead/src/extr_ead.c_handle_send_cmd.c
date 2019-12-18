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
typedef  int /*<<< orphan*/  tn ;
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct ead_msg {int /*<<< orphan*/  type; } ;
struct ead_packet {struct ead_msg msg; } ;
struct ead_msg_cmd_data {int done; int /*<<< orphan*/  data; } ;
struct ead_msg_cmd {scalar_t__* data; int /*<<< orphan*/  timeout; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_2__ {struct ead_msg msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*,int,int /*<<< orphan*/ ,int) ; 
#define  EAD_CMD_BACKGROUND 129 
#define  EAD_CMD_NORMAL 128 
 int EAD_CMD_TIMEOUT ; 
 void* EAD_ENC_DATA (struct ead_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  O_RDWR ; 
 int PCAP_TIMEOUT ; 
 int /*<<< orphan*/  SIGKILL ; 
 int child_pending ; 
 int /*<<< orphan*/  close (int) ; 
 struct ead_msg_cmd* cmd ; 
 int /*<<< orphan*/  cmd_data ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int ead_decrypt_message (struct ead_msg*) ; 
 int /*<<< orphan*/  ead_encrypt_message (struct ead_msg*,int) ; 
 int /*<<< orphan*/  ead_send_packet_clone (struct ead_packet*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fork () ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct timeval*,struct timeval*,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe (int*) ; 
 TYPE_1__* pktbuf ; 
 int read (int,int /*<<< orphan*/ ,int) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  system (char*) ; 

__attribute__((used)) static bool
handle_send_cmd(struct ead_packet *pkt, int len, int *nstate)
{
	struct ead_msg *msg = &pkt->msg;
	struct ead_msg_cmd *cmd = EAD_ENC_DATA(msg, cmd);
	struct ead_msg_cmd_data *cmddata;
	struct timeval tv, to, tn;
	int pfd[2], fd;
	fd_set fds;
	pid_t pid;
	bool stream = false;
	int timeout;
	int type;
	int datalen;

	datalen = ead_decrypt_message(msg) - sizeof(struct ead_msg_cmd);
	if (datalen <= 0)
		return false;

	type = ntohs(cmd->type);
	timeout = ntohs(cmd->timeout);

	FD_ZERO(&fds);
	cmd->data[datalen] = 0;
	switch(type) {
	case EAD_CMD_NORMAL:
		if (pipe(pfd) < 0)
			return false;

		fcntl(pfd[0], F_SETFL, O_NONBLOCK | fcntl(pfd[0], F_GETFL));
		child_pending = true;
		pid = fork();
		if (pid == 0) {
			close(pfd[0]);
			fd = open("/dev/null", O_RDWR);
			if (fd > 0) {
				dup2(fd, 0);
				dup2(pfd[1], 1);
				dup2(pfd[1], 2);
			}
			system((char *)cmd->data);
			exit(0);
		} else if (pid > 0) {
			close(pfd[1]);
			if (!timeout)
				timeout = EAD_CMD_TIMEOUT;

			stream = true;
			break;
		}
		return false;
	case EAD_CMD_BACKGROUND:
		pid = fork();
		if (pid == 0) {
			/* close stdin, stdout, stderr, replace with fd to /dev/null */
			fd = open("/dev/null", O_RDWR);
			if (fd > 0) {
				dup2(fd, 0);
				dup2(fd, 1);
				dup2(fd, 2);
			}
			system((char *)cmd->data);
			exit(0);
		} else if (pid > 0) {
			break;
		}
		return false;
	default:
		return false;
	}

	msg = &pktbuf->msg;
	cmddata = EAD_ENC_DATA(msg, cmd_data);

	if (stream) {
		int nfds, bytes;

		/* send keepalive packets every 200 ms so that the client doesn't timeout */
		gettimeofday(&to, NULL);
		memcpy(&tn, &to, sizeof(tn));
		tv.tv_usec = PCAP_TIMEOUT * 1000;
		tv.tv_sec = 0;
		do {
			cmddata->done = 0;
			FD_SET(pfd[0], &fds);
			nfds = select(pfd[0] + 1, &fds, NULL, NULL, &tv);
			bytes = 0;
			if (nfds > 0) {
				bytes = read(pfd[0], cmddata->data, 1024);
				if (bytes < 0)
					bytes = 0;
			}
			if (!bytes && !child_pending)
				break;
			DEBUG(3, "Sending %d bytes of console data, type=%d, timeout=%d\n", bytes, ntohl(msg->type), timeout);
			ead_encrypt_message(msg, sizeof(struct ead_msg_cmd_data) + bytes);
			ead_send_packet_clone(pkt);
			gettimeofday(&tn, NULL);
		} while (tn.tv_sec < to.tv_sec + timeout);
		if (child_pending) {
			kill(pid, SIGKILL);
			return false;
		}
	}
	cmddata->done = 1;
	ead_encrypt_message(msg, sizeof(struct ead_msg_cmd_data));

	return true;
}