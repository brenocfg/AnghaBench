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
struct timespec {int /*<<< orphan*/  tv_nsec; scalar_t__ tv_sec; } ;
struct flock {int /*<<< orphan*/  l_type; int /*<<< orphan*/  l_whence; scalar_t__ l_len; scalar_t__ l_start; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  F_SETLKW ; 
 int /*<<< orphan*/  F_UNLCK ; 
 int /*<<< orphan*/  F_WRLCK ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  VIS_CSTYLE ; 
 int /*<<< orphan*/  VIS_OCTAL ; 
 char const* destdir ; 
 char* digest ; 
 scalar_t__ dopreserve ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct flock*) ; 
 char* fflags ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* group ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  metafile ; 
 int /*<<< orphan*/  metafp ; 
 int mode ; 
 char* owner ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 
 int /*<<< orphan*/  strsvis (char*,char const*,int /*<<< orphan*/ ,char const*) ; 
 char* tags ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
metadata_log(const char *path, const char *type, struct timespec *ts,
	const char *slink, const char *digestresult, off_t size)
{
	static const char extra[] = { ' ', '\t', '\n', '\\', '#', '\0' };
	const char *p;
	char *buf;
	size_t destlen;
	struct flock metalog_lock;

	if (!metafp)	
		return;
	/* Buffer for strsvis(3). */
	buf = (char *)malloc(4 * strlen(path) + 1);
	if (buf == NULL) {
		warnx("%s", strerror(ENOMEM));
		return;
	}

	/* Lock log file. */
	metalog_lock.l_start = 0;
	metalog_lock.l_len = 0;
	metalog_lock.l_whence = SEEK_SET;
	metalog_lock.l_type = F_WRLCK;
	if (fcntl(fileno(metafp), F_SETLKW, &metalog_lock) == -1) {
		warn("can't lock %s", metafile);
		free(buf);
		return;
	}

	/* Remove destdir. */
	p = path;
	if (destdir) {
		destlen = strlen(destdir);
		if (strncmp(p, destdir, destlen) == 0 &&
		    (p[destlen] == '/' || p[destlen] == '\0'))
			p += destlen;
	}
	while (*p && *p == '/')
		p++;
	strsvis(buf, p, VIS_OCTAL, extra);
	p = buf;
	/* Print details. */
	fprintf(metafp, ".%s%s type=%s", *p ? "/" : "", p, type);
	if (owner)
		fprintf(metafp, " uname=%s", owner);
	if (group)
		fprintf(metafp, " gname=%s", group);
	fprintf(metafp, " mode=%#o", mode);
	if (slink) {
		strsvis(buf, slink, VIS_CSTYLE, extra);	/* encode link */
		fprintf(metafp, " link=%s", buf);
	}
	if (*type == 'f') /* type=file */
		fprintf(metafp, " size=%lld", (long long)size);
	if (ts != NULL && dopreserve)
		fprintf(metafp, " time=%lld.%09ld",
			(long long)ts[1].tv_sec, ts[1].tv_nsec);
	if (digestresult && digest)
		fprintf(metafp, " %s=%s", digest, digestresult);
	if (fflags)
		fprintf(metafp, " flags=%s", fflags);
	if (tags)
		fprintf(metafp, " tags=%s", tags);
	fputc('\n', metafp);
	/* Flush line. */
	fflush(metafp);

	/* Unlock log file. */
	metalog_lock.l_type = F_UNLCK;
	if (fcntl(fileno(metafp), F_SETLKW, &metalog_lock) == -1)
		warn("can't unlock %s", metafile);
	free(buf);
}