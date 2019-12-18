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
struct strbuf {int len; char* buf; scalar_t__ maxlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ putmsg (int,struct strbuf*,struct strbuf*,int) ; 

__attribute__((used)) static int
send_request(int fd, char *ptr, int len, char *what, char *ebuf)
{
	struct	strbuf	ctl;
	int	flags;

	ctl.maxlen = 0;
	ctl.len = len;
	ctl.buf = ptr;

	flags = 0;
	if (putmsg(fd, &ctl, (struct strbuf *) NULL, flags) < 0) {
		pcap_fmt_errmsg_for_errno(ebuf, PCAP_ERRBUF_SIZE,
		    errno, "send_request: putmsg \"%s\"", what);
		return (-1);
	}
	return (0);
}