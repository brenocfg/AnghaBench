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
struct xferstat {int dummy; } ;
struct url_stat {int size; scalar_t__ mtime; scalar_t__ atime; } ;
struct url {char const* scheme; scalar_t__ ims_time; size_t offset; int /*<<< orphan*/  doc; int /*<<< orphan*/ * host; } ;
struct timeval {long tv_sec; scalar_t__ tv_usec; } ;
struct stat {scalar_t__ st_mtime; int st_size; int st_mode; scalar_t__ st_dev; scalar_t__ st_ino; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; } ;
typedef  size_t off_t ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ALLPERMS ; 
 scalar_t__ A_flag ; 
 size_t B_size ; 
 scalar_t__ EINTR ; 
 scalar_t__ ENOENT ; 
 scalar_t__ ETIMEDOUT ; 
 scalar_t__ FETCH_OK ; 
 int /*<<< orphan*/  F_flag ; 
#define  PF_INET 129 
#define  PF_INET6 128 
 scalar_t__ R_flag ; 
 char* SCHEME_FILE ; 
 char* SCHEME_FTP ; 
 char* SCHEME_HTTP ; 
 char* SCHEME_HTTPS ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SIGINFO ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int S_IFREG ; 
 scalar_t__ S_ISREG (int) ; 
 int S_size ; 
 int T_secs ; 
 scalar_t__ U_flag ; 
 int /*<<< orphan*/  _IOFBF ; 
 int /*<<< orphan*/  alarm (unsigned int) ; 
 int /*<<< orphan*/  asprintf (char**,char*,int,char const*,char const*) ; 
 char* buf ; 
 int /*<<< orphan*/  chmod (char*,int) ; 
 int /*<<< orphan*/  chown (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ *) ; 
 scalar_t__ d_flag ; 
 scalar_t__ errno ; 
 int family ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int fetchDebug ; 
 int /*<<< orphan*/  fetchFreeURL (struct url*) ; 
 scalar_t__ fetchLastErrCode ; 
 char const* fetchLastErrString ; 
 struct url* fetchParseURL (char*) ; 
 int fetchStat (struct url*,struct url_stat*,char*) ; 
 unsigned int fetchTimeout ; 
 int /*<<< orphan*/ * fetchXGet (struct url*,struct url_stat*,char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,long) ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fseeko (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int ftp_timeout ; 
 size_t fwrite (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int http_timeout ; 
 char const* i_filename ; 
 scalar_t__ i_flag ; 
 scalar_t__ l_flag ; 
 scalar_t__ m_flag ; 
 int mkstemps (char*,scalar_t__) ; 
 int /*<<< orphan*/  n_flag ; 
 scalar_t__ o_stdout ; 
 scalar_t__ p_flag ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ r_flag ; 
 int rename (char*,char const*) ; 
 scalar_t__ s_flag ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sig_handler ; 
 int sigalrm ; 
 int siginfo ; 
 int sigint ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  stat_end (struct xferstat*) ; 
 int /*<<< orphan*/  stat_start (struct xferstat*,char const*,int,size_t) ; 
 int /*<<< orphan*/  stat_update (struct xferstat*,size_t) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char const*,char*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncasecmp (int /*<<< orphan*/ *,char*,int) ; 
 char* strrchr (char const*,char) ; 
 int symlink (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 scalar_t__ utimes (char*,struct timeval*) ; 
 int v_level ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
fetch(char *URL, const char *path)
{
	struct url *url;
	struct url_stat us;
	struct stat sb, nsb;
	struct xferstat xs;
	FILE *f, *of;
	size_t size, readcnt, wr;
	off_t count;
	char flags[8];
	const char *slash;
	char *tmppath;
	int r;
	unsigned timeout;
	char *ptr;

	f = of = NULL;
	tmppath = NULL;

	timeout = 0;
	*flags = 0;
	count = 0;

	/* set verbosity level */
	if (v_level > 1)
		strcat(flags, "v");
	if (v_level > 2)
		fetchDebug = 1;

	/* parse URL */
	url = NULL;
	if (*URL == '\0') {
		warnx("empty URL");
		goto failure;
	}
	if ((url = fetchParseURL(URL)) == NULL) {
		warnx("%s: parse error", URL);
		goto failure;
	}

	/* if no scheme was specified, take a guess */
	if (!*url->scheme) {
		if (!*url->host)
			strcpy(url->scheme, SCHEME_FILE);
		else if (strncasecmp(url->host, "ftp.", 4) == 0)
			strcpy(url->scheme, SCHEME_FTP);
		else if (strncasecmp(url->host, "www.", 4) == 0)
			strcpy(url->scheme, SCHEME_HTTP);
	}

	/* common flags */
	switch (family) {
	case PF_INET:
		strcat(flags, "4");
		break;
	case PF_INET6:
		strcat(flags, "6");
		break;
	}

	/* FTP specific flags */
	if (strcmp(url->scheme, SCHEME_FTP) == 0) {
		if (p_flag)
			strcat(flags, "p");
		if (d_flag)
			strcat(flags, "d");
		if (U_flag)
			strcat(flags, "l");
		timeout = T_secs ? T_secs : ftp_timeout;
	}

	/* HTTP specific flags */
	if (strcmp(url->scheme, SCHEME_HTTP) == 0 ||
	    strcmp(url->scheme, SCHEME_HTTPS) == 0) {
		if (d_flag)
			strcat(flags, "d");
		if (A_flag)
			strcat(flags, "A");
		timeout = T_secs ? T_secs : http_timeout;
		if (i_flag) {
			if (stat(i_filename, &sb)) {
				warn("%s: stat()", i_filename);
				goto failure;
			}
			url->ims_time = sb.st_mtime;
			strcat(flags, "i");
		}
	}

	/* set the protocol timeout. */
	fetchTimeout = timeout;

	/* just print size */
	if (s_flag) {
		if (timeout)
			alarm(timeout);
		r = fetchStat(url, &us, flags);
		if (timeout)
			alarm(0);
		if (sigalrm || sigint)
			goto signal;
		if (r == -1) {
			warnx("%s", fetchLastErrString);
			goto failure;
		}
		if (us.size == -1)
			printf("Unknown\n");
		else
			printf("%jd\n", (intmax_t)us.size);
		goto success;
	}

	/*
	 * If the -r flag was specified, we have to compare the local
	 * and remote files, so we should really do a fetchStat()
	 * first, but I know of at least one HTTP server that only
	 * sends the content size in response to GET requests, and
	 * leaves it out of replies to HEAD requests.  Also, in the
	 * (frequent) case that the local and remote files match but
	 * the local file is truncated, we have sufficient information
	 * before the compare to issue a correct request.  Therefore,
	 * we always issue a GET request as if we were sure the local
	 * file was a truncated copy of the remote file; we can drop
	 * the connection later if we change our minds.
	 */
	sb.st_size = -1;
	if (!o_stdout) {
		r = stat(path, &sb);
		if (r == 0 && r_flag && S_ISREG(sb.st_mode)) {
			url->offset = sb.st_size;
		} else if (r == -1 || !S_ISREG(sb.st_mode)) {
			/*
			 * Whatever value sb.st_size has now is either
			 * wrong (if stat(2) failed) or irrelevant (if the
			 * path does not refer to a regular file)
			 */
			sb.st_size = -1;
		}
		if (r == -1 && errno != ENOENT) {
			warnx("%s: stat()", path);
			goto failure;
		}
	}

	/* start the transfer */
	if (timeout)
		alarm(timeout);
	f = fetchXGet(url, &us, flags);
	if (timeout)
		alarm(0);
	if (sigalrm || sigint)
		goto signal;
	if (f == NULL) {
		warnx("%s: %s", URL, fetchLastErrString);
		if (i_flag && (strcmp(url->scheme, SCHEME_HTTP) == 0 ||
		    strcmp(url->scheme, SCHEME_HTTPS) == 0) &&
		    fetchLastErrCode == FETCH_OK &&
		    strcmp(fetchLastErrString, "Not Modified") == 0) {
			/* HTTP Not Modified Response, return OK. */
			r = 0;
			goto done;
		} else
			goto failure;
	}
	if (sigint)
		goto signal;

	/* check that size is as expected */
	if (S_size) {
		if (us.size == -1) {
			warnx("%s: size unknown", URL);
		} else if (us.size != S_size) {
			warnx("%s: size mismatch: expected %jd, actual %jd",
			    URL, (intmax_t)S_size, (intmax_t)us.size);
			goto failure;
		}
	}

	/* symlink instead of copy */
	if (l_flag && strcmp(url->scheme, "file") == 0 && !o_stdout) {
		if (symlink(url->doc, path) == -1) {
			warn("%s: symlink()", path);
			goto failure;
		}
		goto success;
	}

	if (us.size == -1 && !o_stdout && v_level > 0)
		warnx("%s: size of remote file is not known", URL);
	if (v_level > 1) {
		if (sb.st_size != -1)
			fprintf(stderr, "local size / mtime: %jd / %ld\n",
			    (intmax_t)sb.st_size, (long)sb.st_mtime);
		if (us.size != -1)
			fprintf(stderr, "remote size / mtime: %jd / %ld\n",
			    (intmax_t)us.size, (long)us.mtime);
	}

	/* open output file */
	if (o_stdout) {
		/* output to stdout */
		of = stdout;
	} else if (r_flag && sb.st_size != -1) {
		/* resume mode, local file exists */
		if (!F_flag && us.mtime && sb.st_mtime != us.mtime) {
			/* no match! have to refetch */
			fclose(f);
			/* if precious, warn the user and give up */
			if (R_flag) {
				warnx("%s: local modification time "
				    "does not match remote", path);
				goto failure_keep;
			}
		} else if (url->offset > sb.st_size) {
			/* gap between what we asked for and what we got */
			warnx("%s: gap in resume mode", URL);
			fclose(of);
			of = NULL;
			/* picked up again later */
		} else if (us.size != -1) {
			if (us.size == sb.st_size)
				/* nothing to do */
				goto success;
			if (sb.st_size > us.size) {
				/* local file too long! */
				warnx("%s: local file (%jd bytes) is longer "
				    "than remote file (%jd bytes)", path,
				    (intmax_t)sb.st_size, (intmax_t)us.size);
				goto failure;
			}
			/* we got it, open local file */
			if ((of = fopen(path, "r+")) == NULL) {
				warn("%s: fopen()", path);
				goto failure;
			}
			/* check that it didn't move under our feet */
			if (fstat(fileno(of), &nsb) == -1) {
				/* can't happen! */
				warn("%s: fstat()", path);
				goto failure;
			}
			if (nsb.st_dev != sb.st_dev ||
			    nsb.st_ino != sb.st_ino ||
			    nsb.st_size != sb.st_size) {
				warnx("%s: file has changed", URL);
				fclose(of);
				of = NULL;
				sb = nsb;
				/* picked up again later */
			}
		}
		/* seek to where we left off */
		if (of != NULL && fseeko(of, url->offset, SEEK_SET) != 0) {
			warn("%s: fseeko()", path);
			fclose(of);
			of = NULL;
			/* picked up again later */
		}
	} else if (m_flag && sb.st_size != -1) {
		/* mirror mode, local file exists */
		if (sb.st_size == us.size && sb.st_mtime == us.mtime)
			goto success;
	}

	if (of == NULL) {
		/*
		 * We don't yet have an output file; either this is a
		 * vanilla run with no special flags, or the local and
		 * remote files didn't match.
		 */

		if (url->offset > 0) {
			/*
			 * We tried to restart a transfer, but for
			 * some reason gave up - so we have to restart
			 * from scratch if we want the whole file
			 */
			url->offset = 0;
			if ((f = fetchXGet(url, &us, flags)) == NULL) {
				warnx("%s: %s", URL, fetchLastErrString);
				goto failure;
			}
			if (sigint)
				goto signal;
		}

		/* construct a temp file name */
		if (sb.st_size != -1 && S_ISREG(sb.st_mode)) {
			if ((slash = strrchr(path, '/')) == NULL)
				slash = path;
			else
				++slash;
			asprintf(&tmppath, "%.*s.fetch.XXXXXX.%s",
			    (int)(slash - path), path, slash);
			if (tmppath != NULL) {
				if (mkstemps(tmppath, strlen(slash) + 1) == -1) {
					warn("%s: mkstemps()", path);
					goto failure;
				}
				of = fopen(tmppath, "w");
				chown(tmppath, sb.st_uid, sb.st_gid);
				chmod(tmppath, sb.st_mode & ALLPERMS);
			}
		}
		if (of == NULL)
			of = fopen(path, "w");
		if (of == NULL) {
			warn("%s: open()", path);
			goto failure;
		}
	}
	count = url->offset;

	/* start the counter */
	stat_start(&xs, path, us.size, count);

	sigalrm = siginfo = sigint = 0;

	/* suck in the data */
	setvbuf(f, NULL, _IOFBF, B_size);
	signal(SIGINFO, sig_handler);
	while (!sigint) {
		if (us.size != -1 && us.size - count < B_size &&
		    us.size - count >= 0)
			size = us.size - count;
		else
			size = B_size;
		if (siginfo) {
			stat_end(&xs);
			siginfo = 0;
		}

		if (size == 0)
			break;

		if ((readcnt = fread(buf, 1, size, f)) < size) {
			if (ferror(f) && errno == EINTR && !sigint)
				clearerr(f);
			else if (readcnt == 0)
				break;
		}

		stat_update(&xs, count += readcnt);
		for (ptr = buf; readcnt > 0; ptr += wr, readcnt -= wr)
			if ((wr = fwrite(ptr, 1, readcnt, of)) < readcnt) {
				if (ferror(of) && errno == EINTR && !sigint)
					clearerr(of);
				else
					break;
			}
		if (readcnt != 0)
			break;
	}
	if (!sigalrm)
		sigalrm = ferror(f) && errno == ETIMEDOUT;
	signal(SIGINFO, SIG_DFL);

	stat_end(&xs);

	/*
	 * If the transfer timed out or was interrupted, we still want to
	 * set the mtime in case the file is not removed (-r or -R) and
	 * the user later restarts the transfer.
	 */
 signal:
	/* set mtime of local file */
	if (!n_flag && us.mtime && !o_stdout && of != NULL &&
	    (stat(path, &sb) != -1) && sb.st_mode & S_IFREG) {
		struct timeval tv[2];

		fflush(of);
		tv[0].tv_sec = (long)(us.atime ? us.atime : us.mtime);
		tv[1].tv_sec = (long)us.mtime;
		tv[0].tv_usec = tv[1].tv_usec = 0;
		if (utimes(tmppath ? tmppath : path, tv))
			warn("%s: utimes()", tmppath ? tmppath : path);
	}

	/* timed out or interrupted? */
	if (sigalrm)
		warnx("transfer timed out");
	if (sigint) {
		warnx("transfer interrupted");
		goto failure;
	}

	/* timeout / interrupt before connection completley established? */
	if (f == NULL)
		goto failure;

	if (!sigalrm) {
		/* check the status of our files */
		if (ferror(f))
			warn("%s", URL);
		if (ferror(of))
			warn("%s", path);
		if (ferror(f) || ferror(of))
			goto failure;
	}

	/* did the transfer complete normally? */
	if (us.size != -1 && count < us.size) {
		warnx("%s appears to be truncated: %jd/%jd bytes",
		    path, (intmax_t)count, (intmax_t)us.size);
		goto failure_keep;
	}

	/*
	 * If the transfer timed out and we didn't know how much to
	 * expect, assume the worst (i.e. we didn't get all of it)
	 */
	if (sigalrm && us.size == -1) {
		warnx("%s may be truncated", path);
		goto failure_keep;
	}

 success:
	r = 0;
	if (tmppath != NULL && rename(tmppath, path) == -1) {
		warn("%s: rename()", path);
		goto failure_keep;
	}
	goto done;
 failure:
	if (of && of != stdout && !R_flag && !r_flag)
		if (stat(path, &sb) != -1 && (sb.st_mode & S_IFREG))
			unlink(tmppath ? tmppath : path);
	if (R_flag && tmppath != NULL && sb.st_size == -1)
		rename(tmppath, path); /* ignore errors here */
 failure_keep:
	r = -1;
	goto done;
 done:
	if (f)
		fclose(f);
	if (of && of != stdout)
		fclose(of);
	if (url)
		fetchFreeURL(url);
	if (tmppath != NULL)
		free(tmppath);
	return (r);
}