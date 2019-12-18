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
typedef  int volatile ssize_t ;
typedef  int volatile off_t ;

/* Variables and functions */
 int /*<<< orphan*/  MIN (int volatile,int volatile) ; 
 int volatile bytes ; 
 int errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int read (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timersub (struct timeval*,struct timeval*,struct timeval*) ; 
 int /*<<< orphan*/  ttyout ; 
 int /*<<< orphan*/  usleep (scalar_t__) ; 
 int write (int,char*,int volatile) ; 

__attribute__((used)) static int
copy_bytes(int infd, int outfd, char *buf, size_t bufsize,
	int rate_limit, int hash_interval)
{
	volatile off_t	hashc;
	ssize_t		inc, outc;
	char		*bufp;
	struct timeval	tvthen, tvnow, tvdiff;
	off_t		bufrem, bufchunk;
	int		serr;

	hashc = hash_interval;
	if (rate_limit)
		bufchunk = rate_limit;
	else
		bufchunk = bufsize;

	while (1) {
		if (rate_limit) {
			(void)gettimeofday(&tvthen, NULL);
		}
		errno = 0;
		inc = outc = 0;
					/* copy bufchunk at a time */
		bufrem = bufchunk;
		while (bufrem > 0) {
			inc = read(infd, buf, MIN((off_t)bufsize, bufrem));
			if (inc <= 0)
				goto copy_done;
			bytes += inc;
			bufrem -= inc;
			bufp = buf;
			while (inc > 0) {
				outc = write(outfd, bufp, inc);
				if (outc < 0)
					goto copy_done;
				inc -= outc;
				bufp += outc;
			}
			if (hash_interval) {
				while (bytes >= hashc) {
					(void)putc('#', ttyout);
					hashc += hash_interval;
				}
				(void)fflush(ttyout);
			}
		}
		if (rate_limit) {	/* rate limited; wait if necessary */
			while (1) {
				(void)gettimeofday(&tvnow, NULL);
				timersub(&tvnow, &tvthen, &tvdiff);
				if (tvdiff.tv_sec > 0)
					break;
				usleep(1000000 - tvdiff.tv_usec);
			}
		}
	}

 copy_done:
	serr = errno;
	if (hash_interval && bytes > 0) {
		if (bytes < hash_interval)
			(void)putc('#', ttyout);
		(void)putc('\n', ttyout);
		(void)fflush(ttyout);
	}
	errno = serr;
	if (inc == -1)
		return 1;
	if (outc == -1)
		return 2;

	return 0;
}