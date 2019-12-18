#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct strbuf {int member_0; char* member_2; char* buf; int maxlen; int len; int /*<<< orphan*/  member_1; } ;
struct TYPE_4__ {int cc; int offset; int bufsize; int /*<<< orphan*/ * bp; scalar_t__ buffer; int /*<<< orphan*/  errbuf; int /*<<< orphan*/  fd; scalar_t__ break_loop; } ;
typedef  TYPE_1__ pcap_t ;
typedef  int /*<<< orphan*/  pcap_handler ;
typedef  int /*<<< orphan*/  bpf_u_int32 ;

/* Variables and functions */
#define  EAGAIN 129 
#define  EINTR 128 
 int MAXDLBUF ; 
 int errno ; 
 scalar_t__ getmsg (int /*<<< orphan*/ ,struct strbuf*,struct strbuf*,int*) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int,int,char*) ; 
 int pcap_process_pkts (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
pcap_read_dlpi(pcap_t *p, int cnt, pcap_handler callback, u_char *user)
{
	int cc;
	u_char *bp;
	int flags;
	bpf_u_int32 ctlbuf[MAXDLBUF];
	struct strbuf ctl = {
		MAXDLBUF,
		0,
		(char *)ctlbuf
	};
	struct strbuf data;

	flags = 0;
	cc = p->cc;
	if (cc == 0) {
		data.buf = (char *)p->buffer + p->offset;
		data.maxlen = p->bufsize;
		data.len = 0;
		do {
			/*
			 * Has "pcap_breakloop()" been called?
			 */
			if (p->break_loop) {
				/*
				 * Yes - clear the flag that indicates
				 * that it has, and return -2 to
				 * indicate that we were told to
				 * break out of the loop.
				 */
				p->break_loop = 0;
				return (-2);
			}
			/*
			 * XXX - check for the DLPI primitive, which
			 * would be DL_HP_RAWDATA_IND on HP-UX
			 * if we're in raw mode?
			 */
			ctl.buf = (char *)ctlbuf;
			ctl.maxlen = MAXDLBUF;
			ctl.len = 0;
			if (getmsg(p->fd, &ctl, &data, &flags) < 0) {
				/* Don't choke when we get ptraced */
				switch (errno) {

				case EINTR:
					cc = 0;
					continue;

				case EAGAIN:
					return (0);
				}
				pcap_fmt_errmsg_for_errno(p->errbuf,
				    sizeof(p->errbuf), errno, "getmsg");
				return (-1);
			}
			cc = data.len;
		} while (cc == 0);
		bp = (u_char *)p->buffer + p->offset;
	} else
		bp = p->bp;

	return (pcap_process_pkts(p, callback, user, cnt, bp, cc));
}