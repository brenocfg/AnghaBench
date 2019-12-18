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
struct stat {int st_mode; } ;
struct passwd {char* pw_dir; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  EISDIR ; 
 scalar_t__ ENOENT ; 
 int EOF ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_WRONLY ; 
#define  S_IFDIR 130 
#define  S_IFLNK 129 
 int S_IFMT ; 
#define  S_IFREG 128 
 int base64 ; 
 int base64_decode () ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 int getmode (void*,int /*<<< orphan*/ ) ; 
 struct passwd* getpwnam (char*) ; 
 scalar_t__ iflag ; 
 int /*<<< orphan*/  infile ; 
 int /*<<< orphan*/  infp ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 char* memcpy (char*,char*,size_t) ; 
 char* memmove (char*,char*,size_t) ; 
 scalar_t__ oflag ; 
 int open (char*,int,int) ; 
 char* outfile ; 
 int /*<<< orphan*/ * outfp ; 
 scalar_t__ pflag ; 
 void* setmode (char*) ; 
 scalar_t__ sflag ; 
 int /*<<< orphan*/ * stdout ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int uu_decode () ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  warnc (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
decode2(void)
{
	int flags, fd, mode;
	size_t n, m;
	char *p, *q;
	void *handle;
	struct passwd *pw;
	struct stat st;
	char buf[MAXPATHLEN + 1];

	base64 = 0;
	/* search for header line */
	for (;;) {
		if (fgets(buf, sizeof(buf), infp) == NULL)
			return (EOF);
		p = buf;
		if (strncmp(p, "begin-base64 ", 13) == 0) {
			base64 = 1;
			p += 13;
		} else if (strncmp(p, "begin ", 6) == 0)
			p += 6;
		else
			continue;
		/* p points to mode */
		q = strchr(p, ' ');
		if (q == NULL)
			continue;
		*q++ = '\0';
		/* q points to filename */
		n = strlen(q);
		while (n > 0 && (q[n-1] == '\n' || q[n-1] == '\r'))
			q[--n] = '\0';
		/* found valid header? */
		if (n > 0)
			break;
	}

	handle = setmode(p);
	if (handle == NULL) {
		warnx("%s: unable to parse file mode", infile);
		return (1);
	}
	mode = getmode(handle, 0) & 0666;
	free(handle);

	if (sflag) {
		/* don't strip, so try ~user/file expansion */
		p = NULL;
		pw = NULL;
		if (*q == '~')
			p = strchr(q, '/');
		if (p != NULL) {
			*p = '\0';
			pw = getpwnam(q + 1);
			*p = '/';
		}
		if (pw != NULL) {
			n = strlen(pw->pw_dir);
			if (buf + n > p) {
				/* make room */
				m = strlen(p);
				if (sizeof(buf) < n + m) {
					warnx("%s: bad output filename",
					    infile);
					return (1);
				}
				p = memmove(buf + n, p, m);
			}
			q = memcpy(p - n, pw->pw_dir, n);
		}
	} else {
		/* strip down to leaf name */
		p = strrchr(q, '/');
		if (p != NULL)
			q = p + 1;
	}
	if (!oflag)
		outfile = q;

	/* POSIX says "/dev/stdout" is a 'magic cookie' not a special file. */
	if (pflag || strcmp(outfile, "/dev/stdout") == 0)
		outfp = stdout;
	else {
		flags = O_WRONLY | O_CREAT | O_EXCL;
		if (lstat(outfile, &st) == 0) {
			if (iflag) {
				warnc(EEXIST, "%s: %s", infile, outfile);
				return (0);
			}
			switch (st.st_mode & S_IFMT) {
			case S_IFREG:
			case S_IFLNK:
				/* avoid symlink attacks */
				if (unlink(outfile) == 0 || errno == ENOENT)
					break;
				warn("%s: unlink %s", infile, outfile);
				return (1);
			case S_IFDIR:
				warnc(EISDIR, "%s: %s", infile, outfile);
				return (1);
			default:
				if (oflag) {
					/* trust command-line names */
					flags &= ~O_EXCL;
					break;
				}
				warnc(EEXIST, "%s: %s", infile, outfile);
				return (1);
			}
		} else if (errno != ENOENT) {
			warn("%s: %s", infile, outfile);
			return (1);
		}
		if ((fd = open(outfile, flags, mode)) < 0 ||
		    (outfp = fdopen(fd, "w")) == NULL) {
			warn("%s: %s", infile, outfile);
			return (1);
		}
	}

	if (base64)
		return (base64_decode());
	else
		return (uu_decode());
}