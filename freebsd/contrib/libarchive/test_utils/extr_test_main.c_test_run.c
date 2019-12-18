#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  workdir ;
struct TYPE_2__ {char* name; int failures; int /*<<< orphan*/  (* func ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LC_ALL ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  Sleep (int) ; 
#define  VERBOSITY_PASSFAIL 129 
#define  VERBOSITY_SUMMARY_ONLY 128 
 scalar_t__ assertChdir (char const*) ; 
 int /*<<< orphan*/  assertMakeDir (char*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int failures ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  keep_temp_files ; 
 int /*<<< orphan*/ * logfile ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int skips ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  stub1 () ; 
 int systemf (char*,char*) ; 
 int /*<<< orphan*/  test_summarize (int,int) ; 
 TYPE_1__* tests ; 
 char* testworkdir ; 
 int umask (int) ; 
 int verbosity ; 

__attribute__((used)) static int
test_run(int i, const char *tmpdir)
{
#ifdef PATH_MAX
	char workdir[PATH_MAX];
#else
	char workdir[1024];
#endif
	char logfilename[64];
	int failures_before = failures;
	int skips_before = skips;
	int oldumask;

	switch (verbosity) {
	case VERBOSITY_SUMMARY_ONLY: /* No per-test reports at all */
		break;
	case VERBOSITY_PASSFAIL: /* rest of line will include ok/FAIL marker */
		printf("%3d: %-64s", i, tests[i].name);
		fflush(stdout);
		break;
	default: /* Title of test, details will follow */
		printf("%3d: %s\n", i, tests[i].name);
	}

	/* Chdir to the top-level work directory. */
	if (!assertChdir(tmpdir)) {
		fprintf(stderr,
		    "ERROR: Can't chdir to top work dir %s\n", tmpdir);
		exit(1);
	}
	/* Create a log file for this test. */
	sprintf(logfilename, "%s.log", tests[i].name);
	logfile = fopen(logfilename, "w");
	fprintf(logfile, "%s\n\n", tests[i].name);
	/* Chdir() to a work dir for this specific test. */
	snprintf(workdir, sizeof(workdir), "%s/%s", tmpdir, tests[i].name);
	testworkdir = workdir;
	if (!assertMakeDir(testworkdir, 0755)
	    || !assertChdir(testworkdir)) {
		fprintf(stderr,
		    "ERROR: Can't chdir to work dir %s\n", testworkdir);
		exit(1);
	}
	/* Explicitly reset the locale before each test. */
	setlocale(LC_ALL, "C");
	/* Record the umask before we run the test. */
	umask(oldumask = umask(0));
	/*
	 * Run the actual test.
	 */
	(*tests[i].func)();
	/*
	 * Clean up and report afterwards.
	 */
	testworkdir = NULL;
	/* Restore umask */
	umask(oldumask);
	/* Reset locale. */
	setlocale(LC_ALL, "C");
	/* Reset directory. */
	if (!assertChdir(tmpdir)) {
		fprintf(stderr, "ERROR: Couldn't chdir to temp dir %s\n",
		    tmpdir);
		exit(1);
	}
	/* Report per-test summaries. */
	tests[i].failures = failures - failures_before;
	test_summarize(tests[i].failures, skips - skips_before);
	/* Close the per-test log file. */
	fclose(logfile);
	logfile = NULL;
	/* If there were no failures, we can remove the work dir and logfile. */
	if (tests[i].failures == 0) {
		if (!keep_temp_files && assertChdir(tmpdir)) {
#if defined(_WIN32) && !defined(__CYGWIN__)
			/* Make sure not to leave empty directories.
			 * Sometimes a processing of closing files used by tests
			 * is not done, then rmdir will be failed and it will
			 * leave a empty test directory. So we should wait a few
			 * seconds and retry rmdir. */
			int r, t;
			for (t = 0; t < 10; t++) {
				if (t > 0)
					Sleep(1000);
				r = systemf("rmdir /S /Q %s", tests[i].name);
				if (r == 0)
					break;
			}
			systemf("del %s", logfilename);
#else
			systemf("rm -rf %s", tests[i].name);
			systemf("rm %s", logfilename);
#endif
		}
	}
	/* Return appropriate status. */
	return (tests[i].failures);
}