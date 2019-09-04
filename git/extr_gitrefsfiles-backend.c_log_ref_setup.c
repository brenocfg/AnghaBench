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
struct strbuf {int dummy; } ;
struct files_ref_store {int dummy; } ;

/* Variables and functions */
 scalar_t__ EISDIR ; 
 scalar_t__ ENOENT ; 
 int O_APPEND ; 
 int O_WRONLY ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  adjust_shared_perm (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  files_reflog_path (struct files_ref_store*,struct strbuf*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  open_or_create_logfile ; 
 scalar_t__ raceproof_create_file (char*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ should_autocreate_reflog (char const*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char*,...) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static int log_ref_setup(struct files_ref_store *refs,
			 const char *refname, int force_create,
			 int *logfd, struct strbuf *err)
{
	struct strbuf logfile_sb = STRBUF_INIT;
	char *logfile;

	files_reflog_path(refs, &logfile_sb, refname);
	logfile = strbuf_detach(&logfile_sb, NULL);

	if (force_create || should_autocreate_reflog(refname)) {
		if (raceproof_create_file(logfile, open_or_create_logfile, logfd)) {
			if (errno == ENOENT)
				strbuf_addf(err, "unable to create directory for '%s': "
					    "%s", logfile, strerror(errno));
			else if (errno == EISDIR)
				strbuf_addf(err, "there are still logs under '%s'",
					    logfile);
			else
				strbuf_addf(err, "unable to append to '%s': %s",
					    logfile, strerror(errno));

			goto error;
		}
	} else {
		*logfd = open(logfile, O_APPEND | O_WRONLY, 0666);
		if (*logfd < 0) {
			if (errno == ENOENT || errno == EISDIR) {
				/*
				 * The logfile doesn't already exist,
				 * but that is not an error; it only
				 * means that we won't write log
				 * entries to it.
				 */
				;
			} else {
				strbuf_addf(err, "unable to append to '%s': %s",
					    logfile, strerror(errno));
				goto error;
			}
		}
	}

	if (*logfd >= 0)
		adjust_shared_perm(logfile);

	free(logfile);
	return 0;

error:
	free(logfile);
	return -1;
}