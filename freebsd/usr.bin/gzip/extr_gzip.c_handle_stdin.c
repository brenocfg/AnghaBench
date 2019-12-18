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
struct stat {size_t st_size; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_mode; } ;
typedef  int ssize_t ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  header1 ;
typedef  enum filetype { ____Placeholder_filetype } filetype ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  FT_BZIP2 133 
#define  FT_GZIP 132 
#define  FT_LZ 131 
#define  FT_PACK 130 
#define  FT_XZ 129 
#define  FT_Z 128 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int cat_fd (unsigned char*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fflag ; 
 int file_gettype (unsigned char*) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int gz_uncompress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int*,char*) ; 
 int /*<<< orphan*/  infile ; 
 int /*<<< orphan*/  infile_clear () ; 
 int /*<<< orphan*/  infile_set (char*,size_t) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 scalar_t__ lflag ; 
 int /*<<< orphan*/  maybe_warn (char*) ; 
 int /*<<< orphan*/  maybe_warnx (char*) ; 
 int /*<<< orphan*/  print_list (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_test (char*,int) ; 
 int /*<<< orphan*/  print_verbage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int read_retry (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ tflag ; 
 int unbzip2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int*) ; 
 int unlz (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int*) ; 
 int unpack (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int*) ; 
 int unxz (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int*) ; 
 scalar_t__ vflag ; 
 int /*<<< orphan*/ * zdopen (int /*<<< orphan*/ ) ; 
 int zuncompress (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int*) ; 

__attribute__((used)) static void
handle_stdin(void)
{
	struct stat isb;
	unsigned char header1[4];
	size_t in_size;
	off_t usize, gsize;
	enum filetype method;
	ssize_t bytes_read;
#ifndef NO_COMPRESS_SUPPORT
	FILE *in;
#endif

#ifndef SMALL
	if (fflag == 0 && lflag == 0 && isatty(STDIN_FILENO)) {
		maybe_warnx("standard input is a terminal -- ignoring");
		goto out;
	}
#endif

	if (fstat(STDIN_FILENO, &isb) < 0) {
		maybe_warn("fstat");
		goto out;
	}
	if (S_ISREG(isb.st_mode))
		in_size = isb.st_size;
	else
		in_size = 0;
	infile_set("(stdin)", in_size);

	if (lflag) {
		print_list(STDIN_FILENO, in_size, infile, isb.st_mtime);
		goto out;
	}

	bytes_read = read_retry(STDIN_FILENO, header1, sizeof header1);
	if (bytes_read == -1) {
		maybe_warn("can't read stdin");
		goto out;
	} else if (bytes_read != sizeof(header1)) {
		maybe_warnx("(stdin): unexpected end of file");
		goto out;
	}

	method = file_gettype(header1);
	switch (method) {
	default:
#ifndef SMALL
		if (fflag == 0) {
			maybe_warnx("unknown compression format");
			goto out;
		}
		usize = cat_fd(header1, sizeof header1, &gsize, STDIN_FILENO);
		break;
#endif
	case FT_GZIP:
		usize = gz_uncompress(STDIN_FILENO, STDOUT_FILENO,
			      (char *)header1, sizeof header1, &gsize, "(stdin)");
		break;
#ifndef NO_BZIP2_SUPPORT
	case FT_BZIP2:
		usize = unbzip2(STDIN_FILENO, STDOUT_FILENO,
				(char *)header1, sizeof header1, &gsize);
		break;
#endif
#ifndef NO_COMPRESS_SUPPORT
	case FT_Z:
		if ((in = zdopen(STDIN_FILENO)) == NULL) {
			maybe_warnx("zopen of stdin");
			goto out;
		}

		usize = zuncompress(in, stdout, (char *)header1,
		    sizeof header1, &gsize);
		fclose(in);
		break;
#endif
#ifndef NO_PACK_SUPPORT
	case FT_PACK:
		usize = unpack(STDIN_FILENO, STDOUT_FILENO,
			       (char *)header1, sizeof header1, &gsize);
		break;
#endif
#ifndef NO_XZ_SUPPORT
	case FT_XZ:
		usize = unxz(STDIN_FILENO, STDOUT_FILENO,
			     (char *)header1, sizeof header1, &gsize);
		break;
#endif
#ifndef NO_LZ_SUPPORT
	case FT_LZ:
		usize = unlz(STDIN_FILENO, STDOUT_FILENO,
			     (char *)header1, sizeof header1, &gsize);
		break;
#endif
	}

#ifndef SMALL
        if (vflag && !tflag && usize != -1 && gsize != -1)
		print_verbage(NULL, NULL, usize, gsize);
	if (vflag && tflag)
		print_test("(stdin)", usize != -1);
#else
	(void)&usize;
#endif

out:
	infile_clear();
}