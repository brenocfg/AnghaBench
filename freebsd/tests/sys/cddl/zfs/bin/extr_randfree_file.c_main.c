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
struct flock {void* l_len; void* l_start; int /*<<< orphan*/  l_whence; } ;
typedef  void* off_t ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  F_FREESP ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  SEEK_SET ; 
 void* atoll (int /*<<< orphan*/ ) ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,struct flock*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ malloc (size_t) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (char*) ; 
 size_t write (int,char*,size_t) ; 

int
main(int argc, char *argv[])
{
	char *filename, *buf;
	size_t filesize;
	off_t start_off, off_len;
	int  fd, ch;
	struct flock fl;

	while ((ch = getopt(argc, argv, "l:s:n:")) != EOF) {
		switch (ch) {
		case 'l':
			filesize = atoll(optarg);
			break;
		case 's':
			start_off = atoll(optarg);
			break;
		case 'n':
			off_len = atoll(optarg);
			break;
		default:
			usage(argv[0]);
			break;
		}
	}

	if (optind == argc - 1)
		filename = argv[optind];
	else
		usage(argv[0]);

	buf = (char *)malloc(filesize);

	if ((fd = open(filename, O_RDWR|O_CREAT|O_TRUNC)) < 0) {
		perror("open");
		return (1);
	}
	if (write(fd, buf, filesize) < filesize) {
		perror("write");
		return (1);
	}
#if UNSUPPORTED
	fl.l_whence = SEEK_SET;
	fl.l_start = start_off;
	fl.l_len = off_len;
	if (fcntl(fd, F_FREESP, &fl) != 0) {
		perror("fcntl");
		return (1);
	}
#else
	fprintf(stderr, "fcntl: F_FREESP not supported\n");
	return (1);
#endif

	free(buf);
	return (0);
}