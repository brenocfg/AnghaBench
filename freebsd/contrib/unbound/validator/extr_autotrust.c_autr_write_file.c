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
typedef  int /*<<< orphan*/  tempf ;
struct trust_anchor {TYPE_1__* autr; } ;
struct module_env {scalar_t__ worker; } ;
struct TYPE_2__ {char* file; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FlushFileBuffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  _fileno (int /*<<< orphan*/ *) ; 
 scalar_t__ _get_osfhandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  autr_write_contents (int /*<<< orphan*/ *,char*,struct trust_anchor*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal_exit (char*,char*,...) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ fsync (int /*<<< orphan*/ ) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  log_assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 scalar_t__ rename (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,char*) ; 

void autr_write_file(struct module_env* env, struct trust_anchor* tp)
{
	FILE* out;
	char* fname = tp->autr->file;
	char tempf[2048];
	log_assert(tp->autr);
	if(!env) {
		log_err("autr_write_file: Module environment is NULL.");
		return;
	}
	/* unique name with pid number and thread number */
	snprintf(tempf, sizeof(tempf), "%s.%d-%d", fname, (int)getpid(),
		env->worker?*(int*)env->worker:0);
	verbose(VERB_ALGO, "autotrust: write to disk: %s", tempf);
	out = fopen(tempf, "w");
	if(!out) {
		fatal_exit("could not open autotrust file for writing, %s: %s",
			tempf, strerror(errno));
		return;
	}
	if(!autr_write_contents(out, tempf, tp)) {
		/* failed to write contents (completely) */
		fclose(out);
		unlink(tempf);
		fatal_exit("could not completely write: %s", fname);
		return;
	}
	if(fflush(out) != 0)
		log_err("could not fflush(%s): %s", fname, strerror(errno));
#ifdef HAVE_FSYNC
	if(fsync(fileno(out)) != 0)
		log_err("could not fsync(%s): %s", fname, strerror(errno));
#else
	FlushFileBuffers((HANDLE)_get_osfhandle(_fileno(out)));
#endif
	if(fclose(out) != 0) {
		fatal_exit("could not complete write: %s: %s",
			fname, strerror(errno));
		unlink(tempf);
		return;
	}
	/* success; overwrite actual file */
	verbose(VERB_ALGO, "autotrust: replaced %s", fname);
#ifdef UB_ON_WINDOWS
	(void)unlink(fname); /* windows does not replace file with rename() */
#endif
	if(rename(tempf, fname) < 0) {
		fatal_exit("rename(%s to %s): %s", tempf, fname, strerror(errno));
	}
}