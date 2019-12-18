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
struct timeval {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct stat {int st_size; int /*<<< orphan*/  st_mode; } ;
struct aiocb {int dummy; } ;
typedef  int off_t ;
typedef  int iot_t ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int IOT_READ ; 
 int IOT_WRITE ; 
 int O_DIRECT ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int O_WRONLY ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aio_waitcomplete (struct aiocb**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int atoi (char*) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  choose_aio (int) ; 
 int disk_getsize (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int open (char const*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int random () ; 
 int /*<<< orphan*/  set_aio (struct aiocb*,int /*<<< orphan*/ ,int,int,int,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  timersub (struct timeval*,struct timeval*,struct timeval*) ; 

int
main(int argc, char *argv[])
{
	int fd;
	struct stat sb;
	struct aiocb *aio;
	char **abuf;
	const char *fn;
	int aio_len;
	int io_size, nrun;
	off_t file_size, offset;
	struct aiocb *a;
	int i, n;
	struct timeval st, et, rt;
	float f_rt;
	iot_t iowhat;


	if (argc < 6) {
		printf("Usage: %s <file> <io size> <number of runs> <concurrency> <ro|wo|rw>\n",
		    argv[0]);
		exit(1);
	}

	fn = argv[1];
	io_size = atoi(argv[2]);
	if (io_size <= 0)
		errx(1, "the I/O size must be >0");
	nrun = atoi(argv[3]);
	if (nrun <= 0)
		errx(1, "the number of runs must be >0");
	aio_len = atoi(argv[4]);
	if (aio_len <= 0)
		errx(1, "AIO concurrency must be >0");
	if (strcmp(argv[5], "ro") == 0)
		iowhat = IOT_READ;
	else if (strcmp(argv[5], "rw") == 0)
		iowhat = IOT_READ | IOT_WRITE;
	else if (strcmp(argv[5], "wo") == 0)
		iowhat = IOT_WRITE;
	else
		errx(1, "the I/O type needs to be \"ro\", \"rw\", or \"wo\"!\n");

	/*
	 * Random returns values between 0 and (2^32)-1; only good for 4 gig.
	 * Lets instead treat random() as returning a block offset w/ block size
	 * being "io_size", so we can handle > 4 gig files.
	 */
	if (iowhat == IOT_READ)
		fd = open(fn, O_RDONLY | O_DIRECT);
	else if (iowhat == IOT_WRITE)
		fd = open(fn, O_WRONLY | O_DIRECT);
	else
		fd = open(fn, O_RDWR | O_DIRECT);

	if (fd < 0)
		err(1, "open failed");
	if (fstat(fd, &sb) < 0)
		err(1, "fstat failed");
	if (S_ISREG(sb.st_mode)) {
		file_size = sb.st_size;
	} else if (S_ISBLK(sb.st_mode) || S_ISCHR(sb.st_mode)) {
		file_size = disk_getsize(fd);
	} else
		errx(1, "unknown file type");
	if (file_size <= 0)
		errx(1, "path provided too small");

	printf("File: %s; File size %jd bytes\n", fn, (intmax_t)file_size);

	aio = calloc(aio_len, sizeof(struct aiocb));
	abuf = calloc(aio_len, sizeof(char *));
	for (i = 0; i < aio_len; i++)
		abuf[i] = calloc(1, io_size * sizeof(char));

	/* Fill with the initial contents */
	gettimeofday(&st, NULL);
	for (i = 0; i < aio_len; i++) {
		offset = random() % (file_size / io_size);
		offset *= io_size;
		set_aio(aio + i, choose_aio(iowhat), fd, offset, io_size, abuf[i]);
	}

	for (i = 0; i < nrun; i++) {
		aio_waitcomplete(&a, NULL);
		n = a - aio;
		assert(n < aio_len);
		assert(n >= 0);
		offset = random() % (file_size / io_size);
		offset *= io_size;
		set_aio(aio + n, choose_aio(iowhat), fd, offset, io_size, abuf[n]);
	}

	gettimeofday(&et, NULL);
	timersub(&et, &st, &rt);
	f_rt = ((float) (rt.tv_usec)) / 1000000.0;
	f_rt += (float) (rt.tv_sec);
	printf("Runtime: %.2f seconds, ", f_rt);
	printf("Op rate: %.2f ops/sec, ", ((float) (nrun))  / f_rt);
	printf("Avg transfer rate: %.2f bytes/sec\n", ((float) (nrun)) * ((float)io_size) / f_rt);



	exit(0);
}