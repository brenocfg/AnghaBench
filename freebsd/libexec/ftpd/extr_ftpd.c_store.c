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
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  LOGBYTES (char*,char*,int) ; 
 int /*<<< orphan*/  LOGCMD (char*,char*) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  L_SET ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ TYPE_A ; 
 int byte_count ; 
 int data ; 
 int /*<<< orphan*/ * dataconn (char*,int,char*) ; 
 int fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ fseeko (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int getc (int /*<<< orphan*/ *) ; 
 scalar_t__ guest ; 
 int guniquefd (char*,char**) ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ noguestmod ; 
 int pdata ; 
 int /*<<< orphan*/  perror_reply (int,char*) ; 
 scalar_t__ receive_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reply (int,char*,...) ; 
 scalar_t__ restart_point ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ type ; 

void
store(char *name, char *mode, int unique)
{
	int fd;
	FILE *fout, *din;
	int (*closefunc)(FILE *);

	if (*mode == 'a') {		/* APPE */
		if (unique) {
			/* Programming error */
			syslog(LOG_ERR, "Internal: unique flag to APPE");
			unique = 0;
		}
		if (guest && noguestmod) {
			reply(550, "Appending to existing file denied.");
			goto err;
		}
		restart_point = 0;	/* not affected by preceding REST */
	}
	if (unique)			/* STOU overrides REST */
		restart_point = 0;
	if (guest && noguestmod) {
		if (restart_point) {	/* guest STOR w/REST */
			reply(550, "Modifying existing file denied.");
			goto err;
		} else			/* treat guest STOR as STOU */
			unique = 1;
	}

	if (restart_point)
		mode = "r+";	/* so ASCII manual seek can work */
	if (unique) {
		if ((fd = guniquefd(name, &name)) < 0)
			goto err;
		fout = fdopen(fd, mode);
	} else
		fout = fopen(name, mode);
	closefunc = fclose;
	if (fout == NULL) {
		perror_reply(553, name);
		goto err;
	}
	byte_count = -1;
	if (restart_point) {
		if (type == TYPE_A) {
			off_t i, n;
			int c;

			n = restart_point;
			i = 0;
			while (i++ < n) {
				if ((c=getc(fout)) == EOF) {
					perror_reply(550, name);
					goto done;
				}
				if (c == '\n')
					i++;
			}
			/*
			 * We must do this seek to "current" position
			 * because we are changing from reading to
			 * writing.
			 */
			if (fseeko(fout, 0, SEEK_CUR) < 0) {
				perror_reply(550, name);
				goto done;
			}
		} else if (lseek(fileno(fout), restart_point, L_SET) < 0) {
			perror_reply(550, name);
			goto done;
		}
	}
	din = dataconn(name, -1, "r");
	if (din == NULL)
		goto done;
	if (receive_data(din, fout) == 0) {
		if (unique)
			reply(226, "Transfer complete (unique file name:%s).",
			    name);
		else
			reply(226, "Transfer complete.");
	}
	(void) fclose(din);
	data = -1;
	pdata = -1;
done:
	LOGBYTES(*mode == 'a' ? "append" : "put", name, byte_count);
	(*closefunc)(fout);
	return;
err:
	LOGCMD(*mode == 'a' ? "append" : "put" , name);
	return;
}