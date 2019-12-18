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
typedef  int /*<<< orphan*/  u_char ;
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int au_read_rec (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  auditfilterd_conf (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  present_rawrecord (struct timespec*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  present_tokens (struct timespec*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ quit ; 
 scalar_t__ reread_config ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
mainloop_file(const char *conffile, const char *trailfile, FILE *trail_fp)
{
	struct timespec ts;
	FILE *conf_fp;
	u_char *buf;
	int reclen;

	while (1) {
		/*
		 * On SIGHUP, we reread the configuration file and reopen
		 * the trail file.
		 */
		if (reread_config) {
			reread_config = 0;
			warnx("rereading configuration");
			conf_fp = fopen(conffile, "r");
			if (conf_fp == NULL)
				err(-1, "%s", conffile);
			auditfilterd_conf(conffile, conf_fp);
			fclose(conf_fp);

			fclose(trail_fp);
			trail_fp = fopen(trailfile, "r");
			if (trail_fp == NULL)
				err(-1, "%s", trailfile);
		}
		if (quit) {
			warnx("quitting");
			break;
		}

		/*
		 * For now, be relatively unrobust about incomplete records,
		 * but in the future will want to do better.  Need to look
		 * more at the right blocking and signal behavior here.
		 */
		reclen = au_read_rec(trail_fp, &buf);
		if (reclen == -1)
			continue;
		if (clock_gettime(CLOCK_REALTIME, &ts) < 0)
			err(-1, "clock_gettime");
		present_rawrecord(&ts, buf, reclen);
		present_tokens(&ts, buf, reclen);
		free(buf);
	}
}