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
typedef  int u_int ;
typedef  scalar_t__ u_char ;
struct sshbuf {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int atomicio (int /*<<< orphan*/ ,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  debug3 (char*,unsigned int) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  put_u32 (scalar_t__*,int) ; 
 int sshbuf_len (struct sshbuf*) ; 
 scalar_t__* sshbuf_mutable_ptr (struct sshbuf*) ; 
 int /*<<< orphan*/  vwrite ; 

int
ssh_msg_send(int fd, u_char type, struct sshbuf *m)
{
	u_char buf[5];
	u_int mlen = sshbuf_len(m);

	debug3("ssh_msg_send: type %u", (unsigned int)type & 0xff);

	put_u32(buf, mlen + 1);
	buf[4] = type;		/* 1st byte of payload is mesg-type */
	if (atomicio(vwrite, fd, buf, sizeof(buf)) != sizeof(buf)) {
		error("ssh_msg_send: write");
		return (-1);
	}
	if (atomicio(vwrite, fd, sshbuf_mutable_ptr(m), mlen) != mlen) {
		error("ssh_msg_send: write");
		return (-1);
	}
	return (0);
}