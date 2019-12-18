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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int O_CREAT ; 
 int O_RDONLY ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  buf_size ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  pfatal (char*,char const*) ; 
 scalar_t__ read (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ write (int,int /*<<< orphan*/ ,scalar_t__) ; 

int
copy_file(const char *from, const char *to)
{
	int	tofd, fromfd;
	ssize_t	i;

	tofd = open(to, O_CREAT|O_TRUNC|O_WRONLY, 0666);
	if (tofd < 0)
		return -1;
	fromfd = open(from, O_RDONLY, 0);
	if (fromfd < 0)
		pfatal("internal error, can't reopen %s", from);
	while ((i = read(fromfd, buf, buf_size)) > 0)
		if (write(tofd, buf, i) != i)
			pfatal("write to %s failed", to);
	close(fromfd);
	close(tofd);
	return 0;
}