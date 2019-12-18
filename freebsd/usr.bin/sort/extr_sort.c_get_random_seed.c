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
struct stat {int st_size; scalar_t__ st_dev; scalar_t__ st_ino; int /*<<< orphan*/  st_mode; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  randseed ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  EX_NOINPUT ; 
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,char*,int) ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ getentropy (char*,int) ; 
 int /*<<< orphan*/  md5_ctx ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int open (char const*,int) ; 
 int read (int,char*,int) ; 
 scalar_t__ stat (char*,struct stat*) ; 

__attribute__((used)) static void
get_random_seed(const char *random_source)
{
	char randseed[32];
	struct stat fsb, rsb;
	ssize_t rd;
	int rsfd;

	rsfd = -1;
	rd = sizeof(randseed);

	if (random_source == NULL) {
		if (getentropy(randseed, sizeof(randseed)) < 0)
			err(EX_SOFTWARE, "getentropy");
		goto out;
	}

	rsfd = open(random_source, O_RDONLY | O_CLOEXEC);
	if (rsfd < 0)
		err(EX_NOINPUT, "open: %s", random_source);

	if (fstat(rsfd, &fsb) != 0)
		err(EX_SOFTWARE, "fstat");

	if (!S_ISREG(fsb.st_mode) && !S_ISCHR(fsb.st_mode))
		err(EX_USAGE,
		    "random seed isn't a regular file or /dev/random");

	/*
	 * Regular files: read up to maximum seed size and explicitly
	 * reject longer files.
	 */
	if (S_ISREG(fsb.st_mode)) {
		if (fsb.st_size > (off_t)sizeof(randseed))
			errx(EX_USAGE, "random seed is too large (%jd >"
			    " %zu)!", (intmax_t)fsb.st_size,
			    sizeof(randseed));
		else if (fsb.st_size < 1)
			errx(EX_USAGE, "random seed is too small ("
			    "0 bytes)");

		memset(randseed, 0, sizeof(randseed));

		rd = read(rsfd, randseed, fsb.st_size);
		if (rd < 0)
			err(EX_SOFTWARE, "reading random seed file %s",
			    random_source);
		if (rd < (ssize_t)fsb.st_size)
			errx(EX_SOFTWARE, "short read from %s", random_source);
	} else if (S_ISCHR(fsb.st_mode)) {
		if (stat("/dev/random", &rsb) < 0)
			err(EX_SOFTWARE, "stat");

		if (fsb.st_dev != rsb.st_dev ||
		    fsb.st_ino != rsb.st_ino)
			errx(EX_USAGE, "random seed is a character "
			    "device other than /dev/random");

		if (getentropy(randseed, sizeof(randseed)) < 0)
			err(EX_SOFTWARE, "getentropy");
	}

out:
	if (rsfd >= 0)
		close(rsfd);

	MD5Init(&md5_ctx);
	MD5Update(&md5_ctx, randseed, rd);
}