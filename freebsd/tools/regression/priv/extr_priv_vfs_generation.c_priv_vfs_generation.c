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
struct stat {scalar_t__ st_gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  expect (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpath ; 
 int stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  warn (char*) ; 

void
priv_vfs_generation(int asroot, int injail, struct test *test)
{
	struct stat sb;
	int error;

	error = stat(fpath, &sb);
	if (error < 0)
		warn("priv_vfs_generation(asroot, injail) stat");

	if (sb.st_gen == 0) {
		error = -1;
		errno = EPERM;
	} else
		error = 0;
	if (asroot && injail)
		expect("priv_vfs_generation(asroot, injail)", error, -1,
		    EPERM);
	if (asroot && !injail)
		expect("priv_vfs_generation(asroot, !injail)", error, 0, 0);
	if (!asroot && injail)
		expect("priv_vfs_generation(!asroot, injail)", error, -1,
		    EPERM);
	if (!asroot && !injail)
		expect("priv_vfs_generation(!asroot, !injail)", error, -1,
		    EPERM);
}