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
struct stat {int st_size; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
#define  TYPE_A 130 
#define  TYPE_I 129 
#define  TYPE_L 128 
 char* alloc_buffer (char*,size_t*,struct stat*) ; 
 int byte_count ; 
 int /*<<< orphan*/  ferror (int /*<<< orphan*/ *) ; 
 int fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fstat (int,struct stat*) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handleoobcmd () ; 
 char* mmap (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (char*,int) ; 
 int /*<<< orphan*/  perror_reply (int,char*) ; 
 int read (int,char*,size_t) ; 
 int /*<<< orphan*/  reply (int,char*,...) ; 
 int restart_point ; 
 int /*<<< orphan*/  sec_fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sec_putc (int,int /*<<< orphan*/ *) ; 
 int sec_write (int,char*,int) ; 
 int transflag ; 
 int type ; 
 scalar_t__ urgflag ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void
send_data(FILE *instr, FILE *outstr)
{
	int c, cnt, filefd, netfd;
	static char *buf;
	static size_t bufsize;

	transflag = 1;
	switch (type) {

	case TYPE_A:
	    while ((c = getc(instr)) != EOF) {
		if (urgflag && handleoobcmd())
		    return;
		byte_count++;
		if(c == '\n')
		    sec_putc('\r', outstr);
		sec_putc(c, outstr);
	    }
	    sec_fflush(outstr);
	    transflag = 0;
	    urgflag = 0;
	    if (ferror(instr))
		goto file_err;
	    if (ferror(outstr))
		goto data_err;
	    reply(226, "Transfer complete.");
	    return;

	case TYPE_I:
	case TYPE_L:
#if 0 /* XXX handle urg flag */
#if defined(HAVE_MMAP) && !defined(NO_MMAP)
#ifndef MAP_FAILED
#define MAP_FAILED (-1)
#endif
	    {
		struct stat st;
		char *chunk;
		int in = fileno(instr);
		if(fstat(in, &st) == 0 && S_ISREG(st.st_mode)
		   && st.st_size > 0) {
		    /*
		     * mmap zero bytes has potential of loosing, don't do it.
		     */
		    chunk = mmap(0, st.st_size, PROT_READ,
				 MAP_SHARED, in, 0);
		    if((void *)chunk != (void *)MAP_FAILED) {
			cnt = st.st_size - restart_point;
			sec_write(fileno(outstr), chunk + restart_point, cnt);
			if (munmap(chunk, st.st_size) < 0)
			    warn ("munmap");
			sec_fflush(outstr);
			byte_count = cnt;
			transflag = 0;
			urgflag = 0;
		    }
		}
	    }
#endif
#endif
	if(transflag) {
	    struct stat st;

	    netfd = fileno(outstr);
	    filefd = fileno(instr);
	    buf = alloc_buffer (buf, &bufsize,
				fstat(filefd, &st) >= 0 ? &st : NULL);
	    if (buf == NULL) {
		transflag = 0;
		urgflag = 0;
		perror_reply(451, "Local resource failure: malloc");
		return;
	    }
	    while ((cnt = read(filefd, buf, bufsize)) > 0 &&
		   sec_write(netfd, buf, cnt) == cnt) {
		byte_count += cnt;
		if (urgflag && handleoobcmd())
		    return;
	    }
	    sec_fflush(outstr); /* to end an encrypted stream */
	    transflag = 0;
	    urgflag = 0;
	    if (cnt != 0) {
		if (cnt < 0)
		    goto file_err;
		goto data_err;
	    }
	}
	reply(226, "Transfer complete.");
	return;
	default:
	    transflag = 0;
	    urgflag = 0;
	    reply(550, "Unimplemented TYPE %d in send_data", type);
	    return;
	}

data_err:
	transflag = 0;
	urgflag = 0;
	perror_reply(426, "Data connection");
	return;

file_err:
	transflag = 0;
	urgflag = 0;
	perror_reply(551, "Error on input file");
}