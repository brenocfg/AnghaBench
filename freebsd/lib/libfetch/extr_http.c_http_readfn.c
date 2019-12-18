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
struct httpio {scalar_t__ error; int buf; scalar_t__ bufpos; scalar_t__ buflen; scalar_t__ eof; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int http_fillbuf (struct httpio*,int) ; 
 int /*<<< orphan*/  memcpy (char*,int,int) ; 

__attribute__((used)) static int
http_readfn(void *v, char *buf, int len)
{
	struct httpio *io = (struct httpio *)v;
	int rlen;

	if (io->error)
		return (-1);
	if (io->eof)
		return (0);

	/* empty buffer */
	if (!io->buf || io->bufpos == io->buflen) {
		if ((rlen = http_fillbuf(io, len)) < 0) {
			if ((errno = io->error) == EINTR)
				io->error = 0;
			return (-1);
		} else if (rlen == 0) {
			return (0);
		}
	}

	rlen = io->buflen - io->bufpos;
	if (len < rlen)
		rlen = len;
	memcpy(buf, io->buf + io->bufpos, rlen);
	io->bufpos += rlen;
	return (rlen);
}