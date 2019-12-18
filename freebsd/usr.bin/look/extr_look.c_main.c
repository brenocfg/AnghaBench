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
typedef  int wchar_t ;
typedef  scalar_t__ uintmax_t ;
struct stat {scalar_t__ st_size; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFBIG ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 unsigned char* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  MB_LEN_MAX ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 scalar_t__ SIZE_T_MAX ; 
 unsigned char* _path_words ; 
 int /*<<< orphan*/  close (int) ; 
 int dflag ; 
 int /*<<< orphan*/  err (int,char*,unsigned char const*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fflag ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  longopts ; 
 int look (int*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  mbrtowc (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned char* mmap (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int open (unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int* prepkey (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	struct stat sb;
	int ch, fd, match;
	wchar_t termchar;
	unsigned char *back, *front;
	unsigned const char *file;
	wchar_t *key;

	(void) setlocale(LC_CTYPE, "");

	file = _path_words;
	termchar = L'\0';
	while ((ch = getopt_long(argc, argv, "+adft:", longopts, NULL)) != -1)
		switch(ch) {
		case 'a':
			/* COMPATIBILITY */
			break;
		case 'd':
			dflag = 1;
			break;
		case 'f':
			fflag = 1;
			break;
		case 't':
			if (mbrtowc(&termchar, optarg, MB_LEN_MAX, NULL) !=
			    strlen(optarg))
				errx(2, "invalid termination character");
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc == 0)
		usage();
	if (argc == 1) 			/* But set -df by default. */
		dflag = fflag = 1;
	key = prepkey(*argv++, termchar);
	if (argc >= 2)
		file = *argv++;

	match = 1;

	do {
		if ((fd = open(file, O_RDONLY, 0)) < 0 || fstat(fd, &sb))
			err(2, "%s", file);
		if ((uintmax_t)sb.st_size > (uintmax_t)SIZE_T_MAX)
			errx(2, "%s: %s", file, strerror(EFBIG));
		if (sb.st_size == 0) {
			close(fd);
			continue;
		}
		if ((front = mmap(NULL, (size_t)sb.st_size, PROT_READ, MAP_SHARED, fd, (off_t)0)) == MAP_FAILED)
			err(2, "%s", file);
		back = front + sb.st_size;
		match *= (look(key, front, back));
		close(fd);
	} while (argc-- > 2 && (file = *argv++));

	exit(match);
}