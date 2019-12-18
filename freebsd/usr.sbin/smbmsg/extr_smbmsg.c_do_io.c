#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ word; scalar_t__ byte; } ;
struct TYPE_3__ {void* word; void* byte; } ;
struct smbcmd {int cmd; int rcount; int wcount; unsigned short* rbuf; void** wbuf; TYPE_2__ rdata; TYPE_1__ wdata; int /*<<< orphan*/  slave; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMB_BREAD ; 
 int /*<<< orphan*/  SMB_BWRITE ; 
 int /*<<< orphan*/  SMB_PCALL ; 
 int /*<<< orphan*/  SMB_QUICK_READ ; 
 int /*<<< orphan*/  SMB_QUICK_WRITE ; 
 int /*<<< orphan*/  SMB_READB ; 
 int /*<<< orphan*/  SMB_READW ; 
 int /*<<< orphan*/  SMB_RECVB ; 
 int /*<<< orphan*/  SMB_SENDB ; 
 int /*<<< orphan*/  SMB_WRITEB ; 
 int /*<<< orphan*/  SMB_WRITEW ; 
 char* bytefmt ; 
 int cflag ; 
 int /*<<< orphan*/  fd ; 
 char* fmt ; 
 unsigned short* ibuf ; 
 int iflag ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct smbcmd*) ; 
 void** obuf ; 
 int oflag ; 
 void* oword ; 
 int /*<<< orphan*/  printf (char*,unsigned short) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  slave ; 
 scalar_t__ wflag ; 
 char* wordfmt ; 

__attribute__((used)) static int
do_io(void)
{
	struct smbcmd c;
	int i;

	c.slave = slave;
	c.cmd = cflag;
	c.rcount = 0;
	c.wcount = 0;

	if (fmt == NULL && iflag > 0)
		fmt = wflag? wordfmt: bytefmt;

	if (cflag == -1) {
		/* operations that do not require a command byte */
		if (iflag == -1 && oflag == 0)
			/* 0 bytes output: quick write operation */
			return (ioctl(fd, SMB_QUICK_WRITE, &c));
		else if (iflag == 0 && oflag == -1)
			/* 0 bytes input: quick read operation */
			return (ioctl(fd, SMB_QUICK_READ, &c));
		else if (iflag == 1 && oflag == -1) {
			/* no command, 1 byte input: receive byte op. */
			if (ioctl(fd, SMB_RECVB, &c) == -1)
				return (-1);
			printf(fmt, (unsigned char)c.cmd);
			putchar('\n');
			return (0);
		} else if (iflag == -1 && oflag == 1) {
			/* no command, 1 byte output: send byte op. */
			c.cmd = obuf[0];
			return (ioctl(fd, SMB_SENDB, &c));
		} else
			return (-2);
	}
	if (iflag == 1 && oflag == -1) {
		/* command + 1 byte input: read byte op. */
		if (ioctl(fd, SMB_READB, &c) == -1)
			return (-1);
		printf(fmt, (unsigned char)c.rdata.byte);
		putchar('\n');
		return (0);
	} else if (iflag == -1 && oflag == 1) {
		/* command + 1 byte output: write byte op. */
		c.wdata.byte = obuf[0];
		return (ioctl(fd, SMB_WRITEB, &c));
	} else if (wflag && iflag == 2 && oflag == -1) {
		/* command + 2 bytes input: read word op. */
		if (ioctl(fd, SMB_READW, &c) == -1)
			return (-1);
		printf(fmt, (unsigned short)c.rdata.word);
		putchar('\n');
		return (0);
	} else if (wflag && iflag == -1 && oflag == 2) {
		/* command + 2 bytes output: write word op. */
		c.wdata.word = oword;
		return (ioctl(fd, SMB_WRITEW, &c));
	} else if (wflag && iflag == 2 && oflag == 2) {
		/*
		 * command + 2 bytes output + 2 bytes input:
		 * "process call" op.
		 */
		c.wdata.word = oword;
		if (ioctl(fd, SMB_PCALL, &c) == -1)
			return (-1);
		printf(fmt, (unsigned short)c.rdata.word);
		putchar('\n');
		return (0);
	} else if (iflag > 1 && oflag == -1) {
		/* command + > 1 bytes of input: block read */
		c.rbuf = ibuf;
		c.rcount = iflag;
		if (ioctl(fd, SMB_BREAD, &c) == -1)
			return (-1);
		for (i = 0; i < c.rcount; i++) {
			if (i != 0)
				putchar(' ');
			printf(fmt, ibuf[i]);
		}
		putchar('\n');
		return (0);
	} else if (iflag == -1 && oflag > 1) {
		/* command + > 1 bytes of output: block write */
		c.wbuf = obuf;
		c.wcount = oflag;
		return (ioctl(fd, SMB_BWRITE, &c));
	}

	return (-2);
}