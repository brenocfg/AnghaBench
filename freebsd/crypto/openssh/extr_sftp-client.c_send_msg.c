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
typedef  int /*<<< orphan*/  u_char ;
struct sshbuf {int dummy; } ;
struct sftp_conn {scalar_t__ limit_kbps; int /*<<< orphan*/  bwlimit_out; int /*<<< orphan*/  fd_out; } ;
struct iovec {int iov_len; int /*<<< orphan*/ * iov_base; } ;
typedef  int /*<<< orphan*/  mlen ;

/* Variables and functions */
 int SFTP_MAX_MSG_LENGTH ; 
 int atomiciov6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iovec*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (char*,int) ; 
 int /*<<< orphan*/  put_u32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * sftpio ; 
 int sshbuf_len (struct sshbuf*) ; 
 scalar_t__ sshbuf_ptr (struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_reset (struct sshbuf*) ; 
 int strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writev ; 

__attribute__((used)) static void
send_msg(struct sftp_conn *conn, struct sshbuf *m)
{
	u_char mlen[4];
	struct iovec iov[2];

	if (sshbuf_len(m) > SFTP_MAX_MSG_LENGTH)
		fatal("Outbound message too long %zu", sshbuf_len(m));

	/* Send length first */
	put_u32(mlen, sshbuf_len(m));
	iov[0].iov_base = mlen;
	iov[0].iov_len = sizeof(mlen);
	iov[1].iov_base = (u_char *)sshbuf_ptr(m);
	iov[1].iov_len = sshbuf_len(m);

	if (atomiciov6(writev, conn->fd_out, iov, 2,
	    conn->limit_kbps > 0 ? sftpio : NULL, &conn->bwlimit_out) !=
	    sshbuf_len(m) + sizeof(mlen))
		fatal("Couldn't send packet: %s", strerror(errno));

	sshbuf_reset(m);
}