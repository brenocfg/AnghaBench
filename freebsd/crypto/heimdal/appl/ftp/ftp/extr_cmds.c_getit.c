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
struct tm {int tm_mon; int tm_year; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;
struct stat {int /*<<< orphan*/  st_mtime; scalar_t__ st_size; } ;

/* Variables and functions */
 int COMPLETE ; 
 int MaxPathLen ; 
 int /*<<< orphan*/  another (int*,char***,char*) ; 
 int code ; 
 int command (char*,char*) ; 
 scalar_t__ debug ; 
 char* domap (char*) ; 
 char* dotrans (char*) ; 
 int /*<<< orphan*/  globulize (char**) ; 
 struct tm* gmtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  islower (unsigned char) ; 
 scalar_t__ isupper (unsigned char) ; 
 scalar_t__ mapflag ; 
 scalar_t__ mcase ; 
 scalar_t__ ntflag ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  recvrequest (char*,char*,char*,char*,int,int) ; 
 char* reply_string ; 
 scalar_t__ restart_point ; 
 int sscanf (char*,char*,int*,int*,int*,int*,int*,int*) ; 
 int stat (char*,struct stat*) ; 
 int verbose ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

int
getit(int argc, char **argv, int restartit, char *filemode)
{
	int loc = 0;
	int local_given = 1;
	char *oldargv1, *oldargv2;

	if (argc == 2) {
		argc++;
		local_given = 0;
		argv[2] = argv[1];
		loc++;
	}
	if ((argc < 2 && !another(&argc, &argv, "remote-file")) ||
	    (argc < 3 && !another(&argc, &argv, "local-file"))) {
		printf("usage: %s remote-file [ local-file ]\n", argv[0]);
		code = -1;
		return (0);
	}
	oldargv1 = argv[1];
	oldargv2 = argv[2];
	if (!globulize(&argv[2])) {
		code = -1;
		return (0);
	}
	if (loc && mcase) {
		char *tp = argv[1], *tp2, tmpbuf[MaxPathLen];

		while (*tp && !islower((unsigned char)*tp)) {
			tp++;
		}
		if (!*tp) {
			tp = argv[2];
			tp2 = tmpbuf;
			while ((*tp2 = *tp) != '\0') {
				if (isupper((unsigned char)*tp2)) {
					*tp2 = 'a' + *tp2 - 'A';
				}
				tp++;
				tp2++;
			}
			argv[2] = tmpbuf;
		}
	}
	if (loc && ntflag)
		argv[2] = dotrans(argv[2]);
	if (loc && mapflag)
		argv[2] = domap(argv[2]);
	if (restartit) {
		struct stat stbuf;
		int ret;

		ret = stat(argv[2], &stbuf);
		if (restartit == 1) {
			if (ret < 0) {
				warn("local: %s", argv[2]);
				return (0);
			}
			restart_point = stbuf.st_size;
		} else if (ret == 0) {
			int overbose;
			int cmdret;
			int yy, mo, day, hour, min, sec;
			struct tm *tm;
			time_t mtime = stbuf.st_mtime;

			overbose = verbose;
			if (debug == 0)
				verbose = -1;
			cmdret = command("MDTM %s", argv[1]);
			verbose = overbose;
			if (cmdret != COMPLETE) {
				printf("%s\n", reply_string);
				return (0);
			}
			if (sscanf(reply_string,
				   "%*s %04d%02d%02d%02d%02d%02d",
				   &yy, &mo, &day, &hour, &min, &sec)
			    != 6) {
				printf ("bad MDTM result\n");
				return (0);
			}

			tm = gmtime(&mtime);
			tm->tm_mon++;
			tm->tm_year += 1900;

			if ((tm->tm_year > yy) ||
			    (tm->tm_year == yy &&
			     tm->tm_mon > mo) ||
			    (tm->tm_mon == mo &&
			     tm->tm_mday > day) ||
			    (tm->tm_mday == day &&
			     tm->tm_hour > hour) ||
			    (tm->tm_hour == hour &&
			     tm->tm_min > min) ||
			    (tm->tm_min == min &&
			     tm->tm_sec > sec))
				return (1);
		}
	}

	recvrequest("RETR", argv[2], argv[1], filemode,
		    argv[1] != oldargv1 || argv[2] != oldargv2, local_given);
	restart_point = 0;
	return (0);
}