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

/* Variables and functions */
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int flopen (char const*,int,int) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char const*) ; 

const char *
test_flopen_create(void)
{
	const char *fn = "test_flopen_create";
	const char *result = NULL;
	int fd;

	unlink(fn);
	fd = flopen(fn, O_RDWR|O_CREAT, 0640);
	if (fd < 0) {
		result = strerror(errno);
	} else {
		close(fd);
	}
	unlink(fn);
	return (result);
}