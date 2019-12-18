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
typedef  int /*<<< orphan*/  time_t ;
struct stat {int st_size; int st_blksize; int /*<<< orphan*/  st_mode; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int EOF ; 
 int /*<<< orphan*/  LOGBYTES (char*,char*,int) ; 
 int /*<<< orphan*/  LOGCMD (char*,char*) ; 
 int /*<<< orphan*/  L_SET ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_A ; 
 int byte_count ; 
 int data ; 
 int /*<<< orphan*/ * dataconn (char*,int,char*) ; 
 scalar_t__ errno ; 
 int fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int ftpd_pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ftpd_popen (char*,char*) ; 
 int getc (int /*<<< orphan*/ *) ; 
 scalar_t__ guest ; 
 int /*<<< orphan*/  logxfer (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int pdata ; 
 int /*<<< orphan*/  perror_reply (int,char*) ; 
 int /*<<< orphan*/  reply (int,char*,char*) ; 
 scalar_t__ restart_point ; 
 int /*<<< orphan*/  send_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ stats ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 scalar_t__ type ; 

void
retrieve(char *cmd, char *name)
{
	FILE *fin, *dout;
	struct stat st;
	int (*closefunc)(FILE *);
	time_t start;
	char line[BUFSIZ];

	if (cmd == 0) {
		fin = fopen(name, "r"), closefunc = fclose;
		st.st_size = 0;
	} else {
		(void) snprintf(line, sizeof(line), cmd, name);
		name = line;
		fin = ftpd_popen(line, "r"), closefunc = ftpd_pclose;
		st.st_size = -1;
		st.st_blksize = BUFSIZ;
	}
	if (fin == NULL) {
		if (errno != 0) {
			perror_reply(550, name);
			if (cmd == 0) {
				LOGCMD("get", name);
			}
		}
		return;
	}
	byte_count = -1;
	if (cmd == 0) {
		if (fstat(fileno(fin), &st) < 0) {
			perror_reply(550, name);
			goto done;
		}
		if (!S_ISREG(st.st_mode)) {
			/*
			 * Never sending a raw directory is a workaround
			 * for buggy clients that will attempt to RETR
			 * a directory before listing it, e.g., Mozilla.
			 * Preventing a guest from getting irregular files
			 * is a simple security measure.
			 */
			if (S_ISDIR(st.st_mode) || guest) {
				reply(550, "%s: not a plain file.", name);
				goto done;
			}
			st.st_size = -1;
			/* st.st_blksize is set for all descriptor types */
		}
	}
	if (restart_point) {
		if (type == TYPE_A) {
			off_t i, n;
			int c;

			n = restart_point;
			i = 0;
			while (i++ < n) {
				if ((c=getc(fin)) == EOF) {
					perror_reply(550, name);
					goto done;
				}
				if (c == '\n')
					i++;
			}
		} else if (lseek(fileno(fin), restart_point, L_SET) < 0) {
			perror_reply(550, name);
			goto done;
		}
	}
	dout = dataconn(name, st.st_size, "w");
	if (dout == NULL)
		goto done;
	time(&start);
	send_data(fin, dout, st.st_blksize, st.st_size,
		  restart_point == 0 && cmd == 0 && S_ISREG(st.st_mode));
	if (cmd == 0 && guest && stats && byte_count > 0)
		logxfer(name, byte_count, start);
	(void) fclose(dout);
	data = -1;
	pdata = -1;
done:
	if (cmd == 0)
		LOGBYTES("get", name, byte_count);
	(*closefunc)(fin);
}