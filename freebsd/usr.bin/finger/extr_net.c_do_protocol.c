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
typedef  int wint_t ;
struct msghdr {size_t msg_iovlen; scalar_t__ msg_flags; scalar_t__ msg_controllen; scalar_t__ msg_control; struct iovec* msg_iov; int /*<<< orphan*/  msg_namelen; void* msg_name; } ;
struct iovec {char* iov_base; int iov_len; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; scalar_t__ ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int OUTPUT_MAX ; 
 int _POSIX2_LINE_MAX ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int getwc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iswprint (int) ; 
 int /*<<< orphan*/  iswspace (int) ; 
 scalar_t__ lflag ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  putwchar (int) ; 
 scalar_t__ sendmsg (int,struct msghdr*,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strdup (char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  warn (char*,...) ; 

__attribute__((used)) static int
do_protocol(const char *name, const struct addrinfo *ai)
{
	int cnt, line_len, s;
	FILE *fp;
	wint_t c, lastc;
	struct iovec iov[3];
	struct msghdr msg;
	static char slash_w[] = "/W ";
	static char neteol[] = "\r\n";

	s = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
	if (s < 0) {
		warn("socket(%d, %d, %d)", ai->ai_family, ai->ai_socktype,
		     ai->ai_protocol);
		return -1;
	}

	msg.msg_name = (void *)ai->ai_addr;
	msg.msg_namelen = ai->ai_addrlen;
	msg.msg_iov = iov;
	msg.msg_iovlen = 0;
	msg.msg_control = 0;
	msg.msg_controllen = 0;
	msg.msg_flags = 0;

	/* -l flag for remote fingerd  */
	if (lflag) {
		iov[msg.msg_iovlen].iov_base = slash_w;
		iov[msg.msg_iovlen++].iov_len = 3;
	}
	/* send the name followed by <CR><LF> */
	iov[msg.msg_iovlen].iov_base = strdup(name);
	iov[msg.msg_iovlen++].iov_len = strlen(name);
	iov[msg.msg_iovlen].iov_base = neteol;
	iov[msg.msg_iovlen++].iov_len = 2;

	if (connect(s, ai->ai_addr, ai->ai_addrlen) < 0) {
		warn("connect");
		close(s);
		return -1;
	}

	if (sendmsg(s, &msg, 0) < 0) {
		warn("sendmsg");
		close(s);
		return -1;
	}

	/*
	 * Read from the remote system; once we're connected, we assume some
	 * data.  If none arrives, we hang until the user interrupts.
	 *
	 * If we see a <CR> or a <CR> with the high bit set, treat it as
	 * a newline; if followed by a newline character, only output one
	 * newline.
	 *
	 * Otherwise, all high bits are stripped; if it isn't printable and
	 * it isn't a space, we can simply set the 7th bit.  Every ASCII
	 * character with bit 7 set is printable.
	 */
	lastc = 0;
	if ((fp = fdopen(s, "r")) != NULL) {
		cnt = 0;
		line_len = 0;
		while ((c = getwc(fp)) != EOF) {
			if (++cnt > OUTPUT_MAX) {
				printf("\n\n Output truncated at %d bytes...\n",
					cnt - 1);
				break;
			}
			if (c == 0x0d) {
				if (lastc == '\r')	/* ^M^M - skip dupes */
					continue;
				c = '\n';
				lastc = '\r';
			} else {
				if (!iswprint(c) && !iswspace(c)) {
					c &= 0x7f;
					c |= 0x40;
				}
				if (lastc != '\r' || c != '\n')
					lastc = c;
				else {
					lastc = '\n';
					continue;
				}
			}
			putwchar(c);
			if (c != '\n' && ++line_len > _POSIX2_LINE_MAX) {
				putchar('\\');
				putchar('\n');
				lastc = '\r';
			}
			if (lastc == '\n' || lastc == '\r')
				line_len = 0;
		}
		if (ferror(fp)) {
			/*
			 * Assume that whatever it was set errno...
			 */
			warn("reading from network");
		}
		if (lastc != L'\n')
			putchar('\n');

		fclose(fp);
	}
	return 0;
}