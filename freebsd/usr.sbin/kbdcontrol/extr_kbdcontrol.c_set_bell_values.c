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

/* Variables and functions */
 int /*<<< orphan*/  CONS_BELLTYPE ; 
 int CONS_QUIET_BELL ; 
 int CONS_VISUAL_BELL ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
set_bell_values(char *opt)
{
	int bell, duration, pitch;

	bell = 0;
	duration = 0;
	pitch = 0;
	if (!strncmp(opt, "quiet.", 6)) {
		bell = CONS_QUIET_BELL;
		opt += 6;
	}
	if (!strcmp(opt, "visual"))
		bell |= CONS_VISUAL_BELL;
	else if (!strcmp(opt, "normal"))
		duration = 5, pitch = 800;
	else if (!strcmp(opt, "off"))
		duration = 0, pitch = 0;
	else {
		char		*v1;

		bell = 0;
		duration = strtol(opt, &v1, 0);
		if ((duration < 0) || (*v1 != '.'))
			goto badopt;
		opt = ++v1;
		pitch = strtol(opt, &v1, 0);
		if ((pitch < 0) || (*opt == '\0') || (*v1 != '\0')) {
badopt:
			warnx("argument to -b must be duration.pitch or [quiet.]visual|normal|off");
			return;
		}
		if (pitch != 0)
			pitch = 1193182 / pitch;	/* in Hz */
		duration /= 10;	/* in 10 m sec */
	}

	ioctl(0, CONS_BELLTYPE, &bell);
	if (duration > 0 && pitch > 0)
		fprintf(stderr, "\e[=%d;%dB", pitch, duration);
}