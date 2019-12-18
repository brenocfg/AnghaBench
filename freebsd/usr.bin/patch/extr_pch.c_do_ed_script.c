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
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  TMPOUTNAME ; 
 char* _PATH_RED ; 
 char* buf ; 
 int /*<<< orphan*/  buf_size ; 
 int /*<<< orphan*/  check_only ; 
 int /*<<< orphan*/  chmod (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ copy_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * filearg ; 
 int /*<<< orphan*/  filemode ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ftello (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ignore_signals () ; 
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ move_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_intuit_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outname ; 
 int /*<<< orphan*/  p_input_line ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfp ; 
 scalar_t__ pgets (int) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/  set_signals (int) ; 
 int /*<<< orphan*/  skip_rest_of_patch ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strEQ (char*,char*) ; 
 char* strchr (char*,char) ; 
 int toutkeep ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 scalar_t__ verbose ; 

void
do_ed_script(void)
{
	char	*t;
	off_t	beginning_of_this_line;
	FILE	*pipefp = NULL;
	int	continuation;

	if (!skip_rest_of_patch) {
		if (copy_file(filearg[0], TMPOUTNAME) < 0) {
			unlink(TMPOUTNAME);
			fatal("can't create temp file %s", TMPOUTNAME);
		}
		snprintf(buf, buf_size, "%s%s%s", _PATH_RED,
		    verbose ? " " : " -s ", TMPOUTNAME);
		pipefp = popen(buf, "w");
	}
	for (;;) {
		beginning_of_this_line = ftello(pfp);
		if (pgets(true) == 0) {
			next_intuit_at(beginning_of_this_line, p_input_line);
			break;
		}
		p_input_line++;
		for (t = buf; isdigit((unsigned char)*t) || *t == ','; t++)
			;
		/* POSIX defines allowed commands as {a,c,d,i,s} */
		if (isdigit((unsigned char)*buf) &&
		    (*t == 'a' || *t == 'c' || *t == 'd' || *t == 'i' || *t == 's')) {
			if (pipefp != NULL)
				fputs(buf, pipefp);
			if (*t == 's') {
				for (;;) {
					continuation = 0;
					t = strchr(buf, '\0') - 1;
					while (--t >= buf && *t == '\\')
						continuation = !continuation;
					if (!continuation ||
					    pgets(true) == 0)
						break;
					if (pipefp != NULL)
						fputs(buf, pipefp);
				}
			} else if (*t != 'd') {
				while (pgets(true)) {
					p_input_line++;
					if (pipefp != NULL)
						fputs(buf, pipefp);
					if (strEQ(buf, ".\n"))
						break;
				}
			}
		} else {
			next_intuit_at(beginning_of_this_line, p_input_line);
			break;
		}
	}
	if (pipefp == NULL)
		return;
	fprintf(pipefp, "w\n");
	fprintf(pipefp, "q\n");
	fflush(pipefp);
	pclose(pipefp);
	ignore_signals();
	if (!check_only) {
		if (move_file(TMPOUTNAME, outname) < 0) {
			toutkeep = true;
			chmod(TMPOUTNAME, filemode);
		} else
			chmod(outname, filemode);
	}
	set_signals(1);
}