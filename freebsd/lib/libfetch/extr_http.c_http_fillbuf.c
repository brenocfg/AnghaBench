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
struct httpio {int eof; scalar_t__ chunked; char* buf; int buflen; size_t chunksize; int /*<<< orphan*/  conn; scalar_t__ bufpos; void* error; } ;
typedef  int ssize_t ;

/* Variables and functions */
 void* EPROTO ; 
 void* errno ; 
 int fetch_read (int /*<<< orphan*/ ,char*,int) ; 
 int http_growbuf (struct httpio*,size_t) ; 
 int http_new_chunk (struct httpio*) ; 

__attribute__((used)) static ssize_t
http_fillbuf(struct httpio *io, size_t len)
{
	ssize_t nbytes;
	char ch;

	if (io->error)
		return (-1);
	if (io->eof)
		return (0);

	/* not chunked: just fetch the requested amount */
	if (io->chunked == 0) {
		if (http_growbuf(io, len) == -1)
			return (-1);
		if ((nbytes = fetch_read(io->conn, io->buf, len)) == -1) {
			io->error = errno;
			return (-1);
		}
		io->buflen = nbytes;
		io->bufpos = 0;
		return (io->buflen);
	}

	/* chunked, but we ran out: get the next chunk header */
	if (io->chunksize == 0) {
		switch (http_new_chunk(io)) {
		case -1:
			io->error = EPROTO;
			return (-1);
		case 0:
			io->eof = 1;
			return (0);
		}
	}

	/* fetch the requested amount, but no more than the current chunk */
	if (len > io->chunksize)
		len = io->chunksize;
	if (http_growbuf(io, len) == -1)
		return (-1);
	if ((nbytes = fetch_read(io->conn, io->buf, len)) == -1) {
		io->error = errno;
		return (-1);
	}
	io->bufpos = 0;
	io->buflen = nbytes;
	io->chunksize -= nbytes;

	if (io->chunksize == 0) {
		if (fetch_read(io->conn, &ch, 1) != 1 || ch != '\r' ||
		    fetch_read(io->conn, &ch, 1) != 1 || ch != '\n')
			return (-1);
	}

	return (io->buflen);
}