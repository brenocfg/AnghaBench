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
struct test {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_IO ; 
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  expect (char*,int,int,int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
priv_io(int asroot, int injail, struct test *test)
{
	int error, fd;

	fd = open(DEV_IO, O_RDONLY);
	if (fd < 0)
		error = -1;
	else
		error = 0;
	if (asroot && injail)
		expect("priv_io(asroot, injail)", error, -1, EPERM);
	if (asroot && !injail)
		expect("priv_io(asroot, !injail)", error, 0, 0);
	if (!asroot && injail)
		expect("priv_io(!asroot, injail)", error, -1, EPERM);
	if (!asroot && !injail)
		expect("priv_io(!asroot, !injail)", error, -1, EPERM);
	if (fd != -1)
		close(fd);
}